#ifndef __EVENT_HPP__
#define __EVENT_HPP__

#include <functional>
#include <type_traits>
#include <iostream>
#include <unordered_map>

namespace nk {

	template<typename... Args>
	class Event {

	public:

		using Handler = std::function<void(Args...)>;

	private:

		std::unordered_map<int, Handler> _handlers;
		int _nextId = 0;

	public:


		int Subscribe(Handler handler) {
			int id = _nextId++;
			_handlers[id] = std::move(handler);
			return id;
		}

		void Unsubscribe(int id) {
			_handlers.erase(id);
		}

		void Invoke(Args... args) {
			for (auto& [id, handler] : _handlers) {
				handler(args...);
			}
		}

		void Clear() {
			_handlers.clear();
		}

	};

}

#endif