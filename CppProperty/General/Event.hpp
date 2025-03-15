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

	private:

		std::unordered_map<int, Handler> _handlers;
		int _nextId = 0;

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

		void Unsubscribe(int id) {
			_handlers.erase(id);
		}

		void Invoke(TArgs... args) {
			for (auto& [id, handler] : _handlers) {
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

		int operator=(Handler&& handler) {
			Clear();
			return Subscribe(std::move(handler));
		}

		operator Handler() {
			return [&](TArgs... args) {
				Invoke(args...);
			};
		}

		void operator()(TArgs... args) {
			Invoke(args...);
		}

	};

}

#endif