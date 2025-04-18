//
// Created by CJ on 4/16/2025.
//

#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <fstream>
#include <utility>
#include <functional>

#include "input.h"

struct Loop {
    std::streampos line;
    size_t count;
};

inline std::unordered_map<std::string, Loop> loops; // Map mapping loop labels to loop objects

// Map mapping key strings to their respective KeySyms
inline std::unordered_map<std::string, KeySym> keys { // This is completely hard coded in for speed
    {"lctrl", XK_Control_L},
    {"lshift", XK_Shift_L},
    {"lalt", XK_Alt_L},
    {"lwin", XK_Meta_L} ,
    {"rctrl", XK_Control_R},
    {"rshift", XK_Shift_R},
    {"ralt", XK_Alt_R},
    {"lwin", XK_Super_L},
    {"rwin", XK_Super_R},

    {"a", XK_a},
    {"b", XK_b},
    {"c", XK_c},
    {"d", XK_d},
    {"e", XK_e},
    {"f", XK_f},
    {"g", XK_g},
    {"h", XK_h},
    {"i", XK_i},
    {"j", XK_j},
    {"k", XK_k},
    {"l", XK_l},
    {"m", XK_m},
    {"n", XK_n},
    {"o", XK_o},
    {"p", XK_p},
    {"q", XK_q},
    {"r", XK_r},
    {"s", XK_s},
    {"t", XK_t},
    {"u", XK_u},
    {"v", XK_v},
    {"w", XK_w},
    {"x", XK_x},
    {"y", XK_y},
    {"z", XK_z},

    {"A", XK_A},
    {"B", XK_B},
    {"C", XK_C},
    {"D", XK_D},
    {"E", XK_E},
    {"F", XK_F},
    {"G", XK_G},
    {"H", XK_H},
    {"I", XK_I},
    {"J", XK_J},
    {"K", XK_K},
    {"L", XK_L},
    {"M", XK_M},
    {"N", XK_N},
    {"O", XK_O},
    {"P", XK_P},
    {"Q", XK_Q},
    {"R", XK_R},
    {"S", XK_S},
    {"T", XK_T},
    {"U", XK_U},
    {"V", XK_V},
    {"W", XK_W},
    {"X", XK_X},
    {"Y", XK_Y},
    {"Z", XK_Z},

    {"0", XK_0},
    {"1", XK_1},
    {"2", XK_2},
    {"3", XK_3},
    {"4", XK_4},
    {"5", XK_5},
    {"6", XK_6},
    {"7", XK_7},
    {"8", XK_8},
    {"9", XK_9},

    {"num0", XK_KP_0},
    {"num1", XK_KP_1},
    {"num2", XK_KP_2},
    {"num3", XK_KP_3},
    {"num4", XK_KP_4},
    {"num5", XK_KP_5},
    {"num6", XK_KP_6},
    {"num7", XK_KP_7},
    {"num8", XK_KP_8},
    {"num9", XK_KP_9},

    {"`", XK_grave},        // `
    {"-", XK_minus},        // -
    {"=", XK_equal},        // =
    {"~", XK_asciitilde},   // ~
    {"!", XK_exclam},     // !
    {"@", XK_at},              // @
    {"#", XK_numbersign},    // #
    {"#", XK_dollar},      // $
    {"%", XK_percent},    // %
    {"^", XK_asciicircum}, // ^
    {"&", XK_ampersand}, // &
    {"*", XK_asterisk},  // *
    {"(", XK_parenleft}, // (
    {")", XK_parenright}, // )
    {"[", XK_bracketleft}, // [
    {"]", XK_bracketright}, // ]
    {"{", XK_braceleft}, // {
    {"}", XK_braceright}, // }
    {"_", XK_underscore}, // _
    {"+", XK_plus},

    {"space", XK_space},
    {" ", XK_space},
    {"tab", XK_Tab},
    {"enter", XK_Return},
    {"return", XK_Return},
    {"backspace", XK_BackSpace},
    {"delete", XK_Delete},
    {"del", XK_Delete},
    {"escape", XK_Escape},
    {"esc", XK_Escape},
    {"capslock", XK_Caps_Lock},
    {"caps", XK_Caps_Lock},

    {".", XK_period},
    {",", XK_comma},
    {";", XK_semicolon},
    {":", XK_colon},
    {"?", XK_question},
    {"/", XK_slash},
    {"\\", XK_backslash},
    {"<", XK_less},
    {">", XK_greater},
    {"\"", XK_quotedbl},
    {"\'", XK_quoteleft},
    {"|", XK_bar},

    {"up", XK_Up},
    {"down", XK_Down},
    {"left", XK_Left},
    {"right", XK_Right}


};

inline std::unordered_map<std::string, KeySym> mouseBtns
{
    {"mleft", XK_Pointer_Left},
    {"mright", XK_Pointer_Right}
};

bool start(std::istream& infile);
bool exec(std::string instruction, std::string arg);
std::string getInstruction(std::string line, size_t& captureBracketPos);
std::pair<size_t, size_t> getCaptureBracketPos(std::string line);
std::string getArg(std::string line, std::pair<size_t, size_t> captureBracketPos);
KeySym getKeyFromStr(std::string keyStr);
KeySym getMouseFromStr(std::string mouseStr);
std::pair<int, int> getMousePosFromArg(std::string posStr);

#endif //INTERPRETER_H
