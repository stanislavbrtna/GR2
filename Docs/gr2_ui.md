### Basic concepts
Firstly you need to define gr2 context structure, that holds your UI elements. You need to separately allocate some space for its elements and screens. All gui data are then stored in this structure, so you can have more contexts for separate applications (displays, windows, etc.).

Context can be filled with elements, most basic element is screen.

#### GR2 context
Init new context:

    void gr2_InitContext(gr2context * c, pscgElement *pscgElementsArray, uint16_t elementsCount, pscgScreen *pscgScreens, uint16_t screensCount);

Reset:

    void gr2_ResetContext(gr2context * c);


#### Element constructors
Constructor creates new element and return ID of this new element.
Screen:

    uint16_t pscg_add_screen(gr2context * c);

Button:

    uint16_t pscg_add_button(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t *str, uint16_t screen, gr2context * c);

Vertical and horizontal slider:

    uint16_t pscg_add_slider_v(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, int32_t param, int32_t value, uint16_t screen, gr2context * c);
    uint16_t pscg_add_slider_h(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, int32_t param, int32_t value, uint16_t screen, gr2context * c);
Text field:

    uint16_t pscg_add_text(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t *str, uint16_t screen, gr2context * c);

Progress bar:

    uint16_t pscg_add_progbar_v(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, int32_t param, int32_t value, uint16_t screen, gr2context * c);
Screen frame:
value is id of screen inside the frame.

    uint16_t pscg_add_frame(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, int32_t val, uint16_t screen, gr2context * c);
Color button:
Color of the button backround is its value.

    uint16_t pscg_add_cbutton(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t *str, uint16_t screen, gr2context * c);

Checkbox:

    uint16_t pscg_add_checkbox(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t *str, uint16_t screen, gr2context * c);

Optional image functions (need PPM support)
Image:

    uint16_t pscg_add_image(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t *fname, uint16_t screen, gr2context * c);

Icon (fname)

    uint16_t pscg_add_icon(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint8_t *str, uint8_t *fname, uint16_t screen, gr2context * c);

#### Destroy elements
Works both for screens and elements.

    void pscg_destroy(uint16_t id, gr2context * c);

#### Draw & Push input to screen
Draw the root (or any) screen on display:

    void pscg_draw_screen(int16_t x1, int16_t y1,int16_t x2, int16_t y2, uint16_t screen, uint8_t all, gr2context * con);

After draw of the root screen call draw end function

    void pscg_draw_end(gr2context * con);

Present touch input to root (or any) screen:

    uint8_t pscg_touch_input(int16_t x1, int16_t y1,int16_t x2, int16_t y2,uint16_t touch_x,uint16_t touch_y, gr2EventType event, uint16_t screen, gr2context * con);

Dump screen and its elements to the stdin:

    void pscg_dump_screen(uint16_t id, gr2context * con);

#### Misc getters and setters:
Element value:

    int32_t pscg_get_value(uint16_t id, gr2context * c);
    void pscg_set_value(uint16_t id, int32_t val, gr2context * c);

Element screen:

    void pscg_set_screen(uint16_t id, uint16_t val, gr2context * c);

Element parameter:

    int32_t pscg_get_param(uint16_t id, gr2context * c);
    void pscg_set_param(uint16_t id, int32_t val, gr2context * c);

XY Coordinates/size:
For using XY/WH instead of X1Y1X2Y2 set relative initialisation to 1 with:

    void pscg_set_relative_init(uint8_t val, gr2context * c);

Then init/resize elements and X2 will be width and Y2 heigth.

    void pscg_set_x1y1x2y2(uint16_t id, uint16_t x1, uint16_t y1,uint16_t x2, uint16_t y2, gr2context * c);
    uint16_t pscg_get_x1(uint16_t id, gr2context * c);
    uint16_t pscg_get_x2(uint16_t id, gr2context * c);
    uint16_t pscg_get_y1(uint16_t id, gr2context * c);
    uint16_t pscg_get_y2(uint16_t id, gr2context * c);
    void pscg_set_x1(uint16_t id, uint16_t val, gr2context * c);
    void pscg_set_x2(uint16_t id, uint16_t val, gr2context * c);
    void pscg_set_y1(uint16_t id, uint16_t val, gr2context * c);
    void pscg_set_y2(uint16_t id, uint16_t val, gr2context * c);

String:

    void pscg_set_str(uint16_t id, uint8_t *str, gr2context * c);
    uint8_t * pscg_get_str(uint16_t id, gr2context * c);

Modified flag:

    void pscg_set_modified(uint16_t id, gr2context * c);

Visible flag:

    void pscg_set_visible(uint16_t id, uint16_t vis, gr2context * c);
    uint8_t pscg_get_visible(uint16_t id, gr2context * c);

Grayout (Disable):

    void pscg_set_grayout(uint16_t id, uint8_t val, gr2context * c);
    uint8_t pscg_get_grayout(uint16_t id, gr2context * c);
Size of the font used:

    void pscg_text_set_size(uint16_t id, uint16_t size, gr2context * c);

Text field editability:

    void pscg_text_set_editable(uint16_t id, uint16_t val, gr2context * c);
    uint8_t pscg_text_get_editable(uint16_t id, gr2context * c);
Ghost (currently buttons only):

    void pscg_set_ghost(uint16_t id, uint16_t val, gr2context * c);
    uint8_t pscg_get_ghost(uint16_t id, gr2context * c);

Selected (currently buttons only):

    void pscg_set_select(uint16_t id, uint16_t val, gr2context * c);
    uint8_t pscg_get_select(uint16_t id, gr2context * c);

Deactivate any active input text field:

    void pscg_text_deactivate(gr2context * c);

Set maximum width of text inside text field:

    void pscg_text_set_fit(uint16_t id, uint16_t val, gr2context * c);
    uint8_t pscg_text_get_fit(uint16_t id, gr2context * c);

Activate editable text field (sets its value to 1):

    void pscg_activate_text(uint16_t id, gr2context * c);
    uint8_t pscg_get_text_active(uint16_t id, gr2context * c);

Events:

    gr2EventType pscg_get_event(uint16_t id, gr2context * c);
    void pscg_set_event(uint16_t id, gr2EventType val, gr2context * c);
    void pscg_clear_event(uint16_t id, gr2context * c); //works both for elements and screens
    void pscg_clear_screen_ev(uint16_t id, gr2context * c);
*Short for get event released & clear event:*

    uint8_t gr2_clicked(uint16_t id, gr2context * c);

Additional screen parameters:
Scrolls alter position of content inside the screen:

    uint16_t pscg_get_xscroll(uint16_t id, gr2context * c);
    uint16_t pscg_get_yscroll(uint16_t id, gr2context * c);
    void pscg_set_xscroll(uint16_t id, int16_t val, gr2context * c);
    void pscg_set_yscroll(uint16_t id, int16_t val, gr2context * c);
Screen cell size sets grid for the coordinates of its elements:

    void pscg_set_x_cell(uint16_t id, uint16_t val, gr2context * c);
    void pscg_set_y_cell(uint16_t id, uint16_t val, gr2context * c);
    uint16_t pscg_get_x_cell(uint16_t id, gr2context * c);
    uint16_t pscg_get_y_cell(uint16_t id, gr2context * c);
Sets default screen font:

    void pscg_set_default_font(uint16_t id, uint8_t val, gr2context * c);

GUI color getters/setters:

    void pscg_set_border_color(uint16_t col, gr2context * c);
    uint16_t pscg_get_border_color(gr2context * c);
    void pscg_set_text_color(uint16_t col, gr2context * c);
    uint16_t pscg_get_text_color(gr2context * c);
    void pscg_set_background_color(uint16_t col, gr2context * c);
    uint16_t pscg_get_background_color(gr2context * c);
    void pscg_set_fill_color(uint16_t col, gr2context * c);
    uint16_t pscg_get_fill_color(gr2context * c);
    void pscg_set_active_color(uint16_t col, gr2context * c);
    uint16_t pscg_get_active_color(gr2context * c);

Get current element count:

    uint16_t pscg_get_element_count(gr2context * c);

Set default grid size:

    void pscg_set_grid_size(uint16_t size, gr2context * c);



> Written with [StackEdit](https://stackedit.io/).

