#ifndef __EVENT_VIEW_H__
#define __EVENT_VIEW_H__

//Included resources
#include "Event.h"

namespace df {

	const std::string VIEW_EVENT = "df::view";

    class EventView : public Event {
    private:
        // Tag to associate.
        std::string m_tag;
        // Value for view.
        int m_value;
        // True if change in value, else replace value.
        bool m_delta;

    public:
        // Create view event with tag VIEW EVENT, value 0, and delta false.
        EventView();

        // Create view event with tag, value, and delta as indicated.
        EventView(std::string new_tag, int new_value, bool new_delta);

        // Set tag to new tag.
        void setTag(std::string new_tag);

        // Get tag.
        std::string getTag() const;

        // Set value to new value.
        void setValue(int new_value);

        // Get value.
        int getValue() const;

        // Set delta to new delta.
        void setDelta(bool new_delta);

        // Get delta.
        bool getDelta() const;
    };
}//End of namespace
#endif// __EVENT_VIEW_H__