#ifndef __EVENT_HPP__
#define __EVENT_HPP__

#include <functional>
#include <type_traits>
#include <iostream>
#include <unordered_map>

namespace nk {

	template<typename... TArgs>
	class Event {

	public:

		using Handler = std::function<void(TArgs...)>;

	protected:

		using HandlerTable = std::unordered_map<int, Handler>;

	protected:

		int _nextId = 0;
		HandlerTable _handlers;

	public:

		int Subscribe(const Handler& handler) {
			int id = _nextId++;
			_handlers[id] = handler;
			return id;
		}

		int Subscribe(Handler&& handler) {
			int id = _nextId++;
			_handlers[id] = std::move(handler);
			return id;
		}

		int SubscribeOnce(const Handler& handler) {
			int id = _nextId++;
			_handlers[id] = [this, handler, id](TArgs... args) {
				handler(args...);
				Unsubscribe(id);
			};
			return id;
		}

		void Unsubscribe(int id) {
			_handlers.erase(id);
		}

		void Invoke(TArgs... args) {
			auto handlersCopy = _handlers;
			for (auto& [id, handler] : handlersCopy) {
				handler(args...);
			}
		}

		void Clear() {
			_handlers.clear();
		}

		int operator=(const Handler& handler) {
			Clear();
			return Subscribe(handler);
		}

	public:

		int operator=(Handler&& handler) {
			Clear();
			return Subscribe(std::move(handler));
		}

		void operator()(TArgs... args) {
			Invoke(args...);
		}

		operator Handler() {
			return [&](TArgs... args) {
				Invoke(args...);
			};
		}

	};

}

#endif