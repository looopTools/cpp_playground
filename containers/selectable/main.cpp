#include <vector>
#include <cstdint>
#include <cassert>

template <typename T>
class selectable_vector
{
public:
    selectable_vector() : _selected_item_index(0) {}

    bool select_item(const size_t index)
    {
        if (_items.size() <= index) {
            return false;
        }
        _selected_item_index = index;
        return true;
    }

    bool select_item(const T item) {
        for (size_t i = 0; i < _items.size(); ++i)
        {
            // Assumes that == operator has been implemented for T
            if (item == _items[i]) {
                _selected_item_index = i;
                return true;
            }
        }
        return false;
    }

    T selected_item()
    {
        if (_items.size() == 0){
            return T{0}; // This is just for illustration
        }
        return _items[_selected_item_index];
    }

    void add(T element)
    {
        // Element dublication will not be handled in this case
        // This is just for illustration
        _items.push_back(element);
    }

    void remove(size_t index)
    {
        if (index < _items.size()  )
        {
            if (_selected_item_index == index)
            {
                // We default it to zero just for fun
                _selected_item_index = 0;
            }
            else if (index < _selected_item_index)
            {
                _selected_item_index = _selected_item_index - 1;
            }
            // If the index is larger than the index entry of the selected item it is not effected
            _items.erase(_items.begin() + index);
        }
    }

private:

    size_t _selected_item_index;
    std::vector<T> _items;
};


class element {

public:
    element(size_t value) : _value(value) {}

    bool operator==(const element& other) const
    {
        return _value == other._value;
    }

    size_t value() const
    {
        return _value;
    }

private:
    size_t _value;
};



int main(void)
{


    selectable_vector<element> elements;


    for (size_t i = 0; i < 10; ++i) {
        elements.add({i});
    }


    element e{9};
    elements.select_item(e);

    assert(e.value() == elements.selected_item().value());
    elements.remove(10);
    assert(e.value() == elements.selected_item().value());

    elements.select_item(3);

    e = element{3};
    assert(e.value() == elements.selected_item().value());
    elements.remove(2);
    assert(e.value() == elements.selected_item().value());
    elements.remove(2);
    assert(0 == elements.selected_item().value());



}
