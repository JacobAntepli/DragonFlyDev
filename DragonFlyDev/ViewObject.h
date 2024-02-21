#ifndef __VIEW_OBJECT_H__
#define __VIEW_OBJECT_H__

//Included resources
#include <string>
#include "Object.h"
#include "Event.h"


using namespace std;
namespace df {
    enum ViewObjectLocation {
        UNDEFINED = -1,
        TOP_LEFT,
        TOP_CENTER,
        TOP_RIGHT,
        CENTER_LEFT,
        CENTER_CENTER,
        CENTER_RIGHT,
        BOTTOM_LEFT,
        BOTTOM_CENTER,
        BOTTOM_RIGHT,
    };

    class ViewObject : public Object {
    private:
        // Label for value (e.g., "Points").
        std::string view_string;
        // Value displayed (e.g., points).
        int m_value;
        // True if should draw value.
        bool m_draw_value;
        // True if border around display.
        bool m_border;
        // Color for text (and border).
        Color m_color;
        // Location of ViewObject.
        ViewObjectLocation m_location;

    public:
        // Construct ViewObject.
        // Object settings: SPECTRAL, max alt.
        // ViewObject defaults: border, top center, default color, draw value.
        ViewObject();

        // Draw view string and value.
        virtual int draw() override;

        // Handle 'view' event if tag matches view string (others ignored).
        // Return 0 if ignored, else 1 if handled.
        virtual int eventHandler(const Event* p_e) override;

        // General location of ViewObject on screen.
        void setLocation(ViewObjectLocation new_location);

        // Get general location of ViewObject on screen.
        ViewObjectLocation getLocation() const;

        // Set view value.
        void setValue(int new_value);

        // Get view value.
        int getValue() const;

        // Set view border (true = display border).
        void setBorder(bool new_border);

        // Get view border (true = display border).
        bool getBorder() const;

        // Set view color.
        void setColor(Color new_color);

        // Get view color.
        Color getColor() const;

        // Set view display string.
        void setViewString(std::string new_view_string);

        // Get view display string.
        std::string getViewString() const;

        // Set true to draw value with display string.
        void setDrawValue(bool new_draw_value = true);

        // Get draw value (true if draw value with display string).
        bool getDrawValue() const;
    };

}


#endif//__VIEW_OBJECT_H__
