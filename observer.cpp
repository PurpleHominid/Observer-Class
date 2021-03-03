#include <iostream>
#include <vector> //include support for vectors 
#include <functional> //include support for: std::reference_wrapper
#include <algorithm>  //include support for: std::find_if


class observer {
  public:
		void set_reference(std::string reference) {
			_reference=reference;
		}

		void notify(std::string message)  { 
			std::cout << _reference << " - " << message << "\n";
		}

	private:
		std::string _reference;
};

class subject {
  public:
    void register_observer(observer& o) {
      _observers.push_back(o);
    }

    void notify_observers() {
			//in this section, the colon (:) tells the compiler to iterates the vector (_observers) using 'being' and 'end' iterators
			//see the deregister function for additional examples
			for (observer& o : _observers) { 
				o.notify("notified");
			}
    }

		void deregister_observer(observer& o ) {
			//search the observer vector for the specific observer, if found return 'it'
			auto it = std::find_if( std::begin( _observers ), std::end( _observers ), [ &o ]( observer& element ) -> bool	{ return &element == &o; });
			_observers.erase( it ); //execute the built-in "erase" method to remove the specific observer
		}

  private:
    std::vector <std::reference_wrapper <observer>> _observers;

};


// Notify generic observer objects when an event occurs.
// The observer pattern allows generic observer objects to be
// registered with a subject object and receive notifications
// when certain events occur.

// The `subject` class, defined on [21-44], contains a [`std::vector`](cpp/container/vector) 
// of references to observers [42].  Observers (also known as listeners), in this case, are objects 
// that implement the `observer` class [7-19]. The `register_observer` function [23-25] adds observers 
// to this `std::vector`, which are later to be notified by the `notify_observers` function [27-33].

// We use [`std::reference_wrapper`] (https://en.cppreference.com/w/cpp/utility/functional/reference_wrapper)
// for the elements of the `std::vector` [42], because the standard containers require the element type to be assignable, which normal
// reference types are not

int main() {
	subject s; //instantiate an instance of the subject class 
	observer dog, cat, mouse, duck; //instantiate instance for each possible observer class 

	dog.set_reference("dog"); //execute the observer "set reference"; in this instance it just used to get each an id
	cat.set_reference("cat");
	mouse.set_reference("mouse");
	duck.set_reference("duck");

	s.register_observer(dog); //pass (by reference) a pointer to the specific obverser class
	s.register_observer(cat);
	s.register_observer(mouse);

	std::cout << "\nSending First Notification\n";
	s.notify_observers(); //execute a method on the subject object to push out a notice

	std::cout << "\nRegistering Duck";
	s.register_observer(duck); //register a new observer

	std::cout << "\nSending Second Notification\n";
	s.notify_observers(); //execute a method on the subject object to push out a notice

	std::cout << "\nRemoving Mouse";
	s.deregister_observer(mouse); //deregister mouse

	std::cout << "\nSending Third Notification\n";
	s.notify_observers();

}
