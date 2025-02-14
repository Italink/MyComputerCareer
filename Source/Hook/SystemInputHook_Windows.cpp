#ifdef _WIN32

#include "qnamespace.h"
#include <QDateTime>

static const QPair<QString,uint> KeyTbl[] = {
	{"",Qt::Key_unknown},    //   0   0x00
	{"",Qt::Key_unknown},    //   1   0x01   VK_LBUTTON          | Left mouse button
	{"",Qt::Key_unknown},    //   2   0x02   VK_RBUTTON          | Right mouse button
	{"",Qt::Key_Cancel},     //   3   0x03   VK_CANCEL           | Control-Break processing
	{"",Qt::Key_unknown},    //   4   0x04   VK_MBUTTON          | Middle mouse button
	{"",Qt::Key_unknown},    //   5   0x05   VK_XBUTTON1         | X1 mouse button
	{"",Qt::Key_unknown},    //   6   0x06   VK_XBUTTON2         | X2 mouse button
	{"",Qt::Key_unknown},    //   7   0x07   -- unassigned --
	{"BackSpace",Qt::Key_Backspace},  //   8   0x08   VK_BACK             | BackSpace key
	{"Tab",Qt::Key_Tab},        //   9   0x09   VK_TAB              | Tab key
	{"",Qt::Key_unknown},    //  10   0x0A   -- reserved --
	{"",Qt::Key_unknown},    //  11   0x0B   -- reserved --
	{"Clear",Qt::Key_Clear},      //  12   0x0C   VK_CLEAR            | Clear key
	{"Enter",Qt::Key_Return},     //  13   0x0D   VK_RETURN           | Enter key
	{"",Qt::Key_unknown},    //  14   0x0E   -- unassigned --
	{"",Qt::Key_unknown},    //  15   0x0F   -- unassigned --
	{"Shift",Qt::Key_Shift},      //  16   0x10   VK_SHIFT            | Shift key
	{"Ctrl",Qt::Key_Control},    //  17   0x11   VK_CONTROL          | Ctrl key
	{"Alt",Qt::Key_Alt},        //  18   0x12   VK_MENU             | Alt key
	{"Pause",Qt::Key_Pause},      //  19   0x13   VK_PAUSE            | Pause key
	{"CapsLock",Qt::Key_CapsLock},   //  20   0x14   VK_CAPITAL          | Caps-Lock
	{"",Qt::Key_unknown},    //  21   0x15   VK_KANA / VK_HANGUL | IME Kana or Hangul mode
	{"",Qt::Key_unknown},    //  22   0x16   -- unassigned --
	{"",Qt::Key_unknown},    //  23   0x17   VK_JUNJA            | IME Junja mode
	{"",Qt::Key_unknown},    //  24   0x18   VK_FINAL            | IME final mode
	{"",Qt::Key_unknown},    //  25   0x19   VK_HANJA / VK_KANJI | IME Hanja or Kanji mode
	{"",Qt::Key_unknown},    //  26   0x1A   -- unassigned --
	{"Esc",Qt::Key_Escape},     //  27   0x1B   VK_ESCAPE           | Esc key
	{"",Qt::Key_unknown},    //  28   0x1C   VK_CONVERT          | IME convert
	{"",Qt::Key_unknown},    //  29   0x1D   VK_NONCONVERT       | IME non-convert
	{"",Qt::Key_unknown},    //  30   0x1E   VK_ACCEPT           | IME accept
	{"",Qt::Key_Mode_switch},//  31   0x1F   VK_MODECHANGE       | IME mode change request
	{"Space",Qt::Key_Space},      //  32   0x20   VK_SPACE            | Spacebar
	{"Page Up",Qt::Key_PageUp},     //  33   0x21   VK_PRIOR            | Page Up key
	{"Page Down",Qt::Key_PageDown},   //  34   0x22   VK_NEXT             | Page Down key
	{"End",Qt::Key_End},        //  35   0x23   VK_END              | End key
	{"Home",Qt::Key_Home},       //  36   0x24   VK_HOME             | Home key
	{"Left",Qt::Key_Left},       //  37   0x25   VK_LEFT             | Left arrow key
	{"Up",Qt::Key_Up},         //  38   0x26   VK_UP               | Up arrow key
	{"Right",Qt::Key_Right},      //  39   0x27   VK_RIGHT            | Right arrow key
	{"Down",Qt::Key_Down},       //  40   0x28   VK_DOWN             | Down arrow key
	{"Select",Qt::Key_Select},     //  41   0x29   VK_SELECT           | Select key
	{"Select",Qt::Key_Printer},    //  42   0x2A   VK_PRINT            | c key
	{"Execute",Qt::Key_Execute},    //  43   0x2B   VK_EXECUTE          | Execute key
	{"Print",Qt::Key_Print},      //  44   0x2C   VK_SNAPSHOT         | Print Screen key
	{"Insert",Qt::Key_Insert},     //  45   0x2D   VK_INSERT           | Ins key
	{"Delete",Qt::Key_Delete},     //  46   0x2E   VK_DELETE           | Del key
	{"Help",Qt::Key_Help},       //  47   0x2F   VK_HELP             | Help key
	{"0",0},                  //  48   0x30   (VK_0)              | 0 key
	{"1",0},                  //  49   0x31   (VK_1)              | 1 key
	{"2",0},                  //  50   0x32   (VK_2)              | 2 key
	{"3",0},                  //  51   0x33   (VK_3)              | 3 key
	{"4",0},                  //  52   0x34   (VK_4)              | 4 key
	{"5",0},                  //  53   0x35   (VK_5)              | 5 key
	{"6",0},                  //  54   0x36   (VK_6)              | 6 key
	{"7",0},                  //  55   0x37   (VK_7)              | 7 key
	{"8",0},                  //  56   0x38   (VK_8)              | 8 key
	{"9",0},                  //  57   0x39   (VK_9)              | 9 key
	{"",Qt::Key_unknown},    //  58   0x3A   -- unassigned --
	{"",Qt::Key_unknown},    //  59   0x3B   -- unassigned --
	{"",Qt::Key_unknown},    //  60   0x3C   -- unassigned --
	{"",Qt::Key_unknown},    //  61   0x3D   -- unassigned --
	{"",Qt::Key_unknown},    //  62   0x3E   -- unassigned --
	{"",Qt::Key_unknown},    //  63   0x3F   -- unassigned --
	{"",Qt::Key_unknown},    //  64   0x40   -- unassigned --
	{"A",0},                  //  65   0x41   (VK_A)              | A key
	{"B",0},                  //  66   0x42   (VK_B)              | B key
	{"C",0},                  //  67   0x43   (VK_C)              | C key
	{"D",0},                  //  68   0x44   (VK_D)              | D key
	{"E",0},                  //  69   0x45   (VK_E)              | E key
	{"F",0},                  //  70   0x46   (VK_F)              | F key
	{"G",0},                  //  71   0x47   (VK_G)              | G key
	{"H",0},                  //  72   0x48   (VK_H)              | H key
	{"I",0},                  //  73   0x49   (VK_I)              | I key
	{"J",0},                  //  74   0x4A   (VK_J)              | J key
	{"K",0},                  //  75   0x4B   (VK_K)              | K key
	{"L",0},                  //  76   0x4C   (VK_L)              | L key
	{"M",0},                  //  77   0x4D   (VK_M)              | M key
	{"N",0},                  //  78   0x4E   (VK_N)              | N key
	{"O",0},                  //  79   0x4F   (VK_O)              | O key
	{"P",0},                  //  80   0x50   (VK_P)              | P key
	{"Q",0},                  //  81   0x51   (VK_Q)              | Q key
	{"R",0},                  //  82   0x52   (VK_R)              | R key
	{"S",0},                  //  83   0x53   (VK_S)              | S key
	{"T",0},                  //  84   0x54   (VK_T)              | T key
	{"U",0},                  //  85   0x55   (VK_U)              | U key
	{"V",0},                  //  86   0x56   (VK_V)              | V key
	{"W",0},                  //  87   0x57   (VK_W)              | W key
	{"X",0},                  //  88   0x58   (VK_X)              | X key
	{"Y",0},                  //  89   0x59   (VK_Y)              | Y key
	{"Z",0},                  //  90   0x5A   (VK_Z)              | Z key
	{"Win",Qt::Key_Meta},       //  91   0x5B   VK_LWIN             | Left Windows  - MS Natural kbd
	{"Win",Qt::Key_Meta},       //  92   0x5C   VK_RWIN             | Right Windows - MS Natural kbd
	{"",Qt::Key_Menu},       //  93   0x5D   VK_APPS             | Application key-MS Natural kbd
	{"",Qt::Key_unknown},    //  94   0x5E   -- reserved --
	{"Sleep",Qt::Key_Sleep},      //  95   0x5F   VK_SLEEP
	{"0",Qt::Key_0},          //  96   0x60   VK_NUMPAD0          | Numeric keypad 0 key
	{"1",Qt::Key_1},          //  97   0x61   VK_NUMPAD1          | Numeric keypad 1 key
	{"2",Qt::Key_2},          //  98   0x62   VK_NUMPAD2          | Numeric keypad 2 key
	{"3",Qt::Key_3},          //  99   0x63   VK_NUMPAD3          | Numeric keypad 3 key
	{"4",Qt::Key_4},          // 100   0x64   VK_NUMPAD4          | Numeric keypad 4 key
	{"5",Qt::Key_5},          // 101   0x65   VK_NUMPAD5          | Numeric keypad 5 key
	{"6",Qt::Key_6},          // 102   0x66   VK_NUMPAD6          | Numeric keypad 6 key
	{"7",Qt::Key_7},          // 103   0x67   VK_NUMPAD7          | Numeric keypad 7 key
	{"8",Qt::Key_8},          // 104   0x68   VK_NUMPAD8          | Numeric keypad 8 key
	{"9",Qt::Key_9},          // 105   0x69   VK_NUMPAD9          | Numeric keypad 9 key
	{"*",Qt::Key_Asterisk},   // 106   0x6A   VK_MULTIPLY         | Multiply key
	{"+",Qt::Key_Plus},       // 107   0x6B   VK_ADD              | Add key
	{"",Qt::Key_unknown},    // 108   0x6C   VK_SEPARATOR        | Separator key (locale-dependent)
	{"-",Qt::Key_Minus},      // 109   0x6D   VK_SUBTRACT         | Subtract key
	{"Decimal",Qt::Key_unknown},    // 110   0x6E   VK_DECIMAL          | Decimal key (locale-dependent)
	{"/",Qt::Key_Slash},      // 111   0x6F   VK_DIVIDE           | Divide key
	{"F1",Qt::Key_F1},         // 112   0x70   VK_F1               | F1 key
	{"F2",Qt::Key_F2},         // 113   0x71   VK_F2               | F2 key
	{"F3",Qt::Key_F3},         // 114   0x72   VK_F3               | F3 key
	{"F4",Qt::Key_F4},         // 115   0x73   VK_F4               | F4 key
	{"F5",Qt::Key_F5},         // 116   0x74   VK_F5               | F5 key
	{"F6",Qt::Key_F6},         // 117   0x75   VK_F6               | F6 key
	{"F7",Qt::Key_F7},         // 118   0x76   VK_F7               | F7 key
	{"F8",Qt::Key_F8},         // 119   0x77   VK_F8               | F8 key
	{"F9",Qt::Key_F9},         // 120   0x78   VK_F9               | F9 key
	{"F10",Qt::Key_F10},        // 121   0x79   VK_F10              | F10 key
	{"F11",Qt::Key_F11},        // 122   0x7A   VK_F11              | F11 key
	{"F12",Qt::Key_F12},        // 123   0x7B   VK_F12              | F12 key
	{"F13",Qt::Key_F13},        // 124   0x7C   VK_F13              | F13 key
	{"F14",Qt::Key_F14},        // 125   0x7D   VK_F14              | F14 key
	{"F15",Qt::Key_F15},        // 126   0x7E   VK_F15              | F15 key
	{"F16",Qt::Key_F16},        // 127   0x7F   VK_F16              | F16 key
	{"F17",Qt::Key_F17},        // 128   0x80   VK_F17              | F17 key
	{"F18",Qt::Key_F18},        // 129   0x81   VK_F18              | F18 key
	{"F19",Qt::Key_F19},        // 130   0x82   VK_F19              | F19 key
	{"F20",Qt::Key_F20},        // 131   0x83   VK_F20              | F20 key
	{"F21",Qt::Key_F21},        // 132   0x84   VK_F21              | F21 key
	{"F22",Qt::Key_F22},        // 133   0x85   VK_F22              | F22 key
	{"F23",Qt::Key_F23},        // 134   0x86   VK_F23              | F23 key
	{"F24",Qt::Key_F24},        // 135   0x87   VK_F24              | F24 key
	{"",Qt::Key_unknown},    // 136   0x88   -- unassigned --
	{"",Qt::Key_unknown},    // 137   0x89   -- unassigned --
	{"",Qt::Key_unknown},    // 138   0x8A   -- unassigned --
	{"",Qt::Key_unknown},    // 139   0x8B   -- unassigned --
	{"",Qt::Key_unknown},    // 140   0x8C   -- unassigned --
	{"",Qt::Key_unknown},    // 141   0x8D   -- unassigned --
	{"",Qt::Key_unknown},    // 142   0x8E   -- unassigned --
	{"",Qt::Key_unknown},    // 143   0x8F   -- unassigned --
	{"NumLock",Qt::Key_NumLock},    // 144   0x90   VK_NUMLOCK          | Num Lock key
	{"ScrollLock",Qt::Key_ScrollLock}, // 145   0x91   VK_SCROLL           | Scroll Lock key
	// Fujitsu/OASYS kbd --------------------
	{"",0}, //Qt::Key_Jisho}, // 146   0x92   VK_OEM_FJ_JISHO     | 'Dictionary' key /
	//              VK_OEM_NEC_EQUAL  = key on numpad on NEC PC-9800 kbd
	{"",Qt::Key_Massyo},     // 147   0x93   VK_OEM_FJ_MASSHOU   | 'Unregister word' key
	{"",Qt::Key_Touroku},    // 148   0x94   VK_OEM_FJ_TOUROKU   | 'Register word' key
	{"",0}, //Qt::Key_Oyayubi_Left,//149   0x95  VK_OEM_FJ_LOYA  | 'Left OYAYUBI' key
	{"",0}, //Qt::Key_Oyayubi_Right,//150  0x96  VK_OEM_FJ_ROYA  | 'Right OYAYUBI' key
	{"",Qt::Key_unknown},    // 151   0x97   -- unassigned --
	{"",Qt::Key_unknown},    // 152   0x98   -- unassigned --
	{"",Qt::Key_unknown},    // 153   0x99   -- unassigned --
	{"",Qt::Key_unknown},    // 154   0x9A   -- unassigned --
	{"",Qt::Key_unknown},    // 155   0x9B   -- unassigned --
	{"",Qt::Key_unknown},    // 156   0x9C   -- unassigned --
	{"",Qt::Key_unknown},    // 157   0x9D   -- unassigned --
	{"",Qt::Key_unknown},    // 158   0x9E   -- unassigned --
	{"",Qt::Key_unknown},    // 159   0x9F   -- unassigned --
	{"Shift",Qt::Key_Shift},      // 160   0xA0   VK_LSHIFT           | Left Shift key
	{"Shift",Qt::Key_Shift},      // 161   0xA1   VK_RSHIFT           | Right Shift key
	{"Control",Qt::Key_Control},    // 162   0xA2   VK_LCONTROL         | Left Ctrl ke
	{"Control",Qt::Key_Control},    // 163   0xA3   VK_RCONTROL         | Right Ctrl key
	{"Alt",Qt::Key_Alt},        // 164   0xA4   VK_LMENU            | Left Menu key
	{"Alt",Qt::Key_Alt},        // 165   0xA5   VK_RMENU            | Right Menu key
	{"Back",Qt::Key_Back},       // 166   0xA6   VK_BROWSER_BACK     | Browser Back key
	{"Forward",Qt::Key_Forward},    // 167   0xA7   VK_BROWSER_FORWARD  | Browser Forward key
	{"Refresh",Qt::Key_Refresh},    // 168   0xA8   VK_BROWSER_REFRESH  | Browser Refresh key
	{"",Qt::Key_Stop},       // 169   0xA9   VK_BROWSER_STOP     | Browser Stop key
	{"",Qt::Key_Search},     // 170   0xAA   VK_BROWSER_SEARCH   | Browser Search key
	{"",Qt::Key_Favorites},  // 171   0xAB   VK_BROWSER_FAVORITES| Browser Favorites key
	{"",Qt::Key_HomePage},   // 172   0xAC   VK_BROWSER_HOME     | Browser Start and Home key
	{"",Qt::Key_VolumeMute}, // 173   0xAD   VK_VOLUME_MUTE      | Volume Mute key
	{"",Qt::Key_VolumeDown}, // 174   0xAE   VK_VOLUME_DOWN      | Volume Down key
	{"",Qt::Key_VolumeUp},   // 175   0xAF   VK_VOLUME_UP        | Volume Up key
	{"",Qt::Key_MediaNext},  // 176   0xB0   VK_MEDIA_NEXT_TRACK | Next Track key
	{"",Qt::Key_MediaPrevious}, //177 0xB1   VK_MEDIA_PREV_TRACK | Previous Track key
	{"",Qt::Key_MediaStop},  // 178   0xB2   VK_MEDIA_STOP       | Stop Media key
	{"",Qt::Key_MediaTogglePlayPause},
	// 179   0xB3   VK_MEDIA_PLAY_PAUSE | Play/Pause Media key
	{"",Qt::Key_LaunchMail}, // 180   0xB4   VK_LAUNCH_MAIL      | Start Mail key
	{"",Qt::Key_LaunchMedia},// 181   0xB5   VK_LAUNCH_MEDIA_SELECT Select Media key
	{"",Qt::Key_Launch0},    // 182   0xB6   VK_LAUNCH_APP1      | Start Application 1 key
	{"",Qt::Key_Launch1},    // 183   0xB7   VK_LAUNCH_APP2      | Start Application 2 key
	{"",Qt::Key_unknown},    // 184   0xB8   -- reserved --
	{"",Qt::Key_unknown},    // 185   0xB9   -- reserved --
	{"",0},                  // 186   0xBA   VK_OEM_1            | ';:' for US
	{"",0},                  // 187   0xBB   VK_OEM_PLUS         | '+' any country
	{"",0},                  // 188   0xBC   VK_OEM_COMMA        | ',' any country
	{"",0},                  // 189   0xBD   VK_OEM_MINUS        | '-' any country
	{"",0},                  // 190   0xBE   VK_OEM_PERIOD       | '.' any country
	{"",0},                  // 191   0xBF   VK_OEM_2            | '/?' for US
	{"",0},                  // 192   0xC0   VK_OEM_3            | '`~' for US
	{"",Qt::Key_unknown},    // 193   0xC1   -- reserved --
	{"",Qt::Key_unknown},    // 194   0xC2   -- reserved --
	{"",Qt::Key_unknown},    // 195   0xC3   -- reserved --
	{"",Qt::Key_unknown},    // 196   0xC4   -- reserved --
	{"",Qt::Key_unknown},    // 197   0xC5   -- reserved --
	{"",Qt::Key_unknown},    // 198   0xC6   -- reserved --
	{"",Qt::Key_unknown},    // 199   0xC7   -- reserved --
	{"",Qt::Key_unknown},    // 200   0xC8   -- reserved --
	{"",Qt::Key_unknown},    // 201   0xC9   -- reserved --
	{"",Qt::Key_unknown},    // 202   0xCA   -- reserved --
	{"",Qt::Key_unknown},    // 203   0xCB   -- reserved --
	{"",Qt::Key_unknown},    // 204   0xCC   -- reserved --
	{"",Qt::Key_unknown},    // 205   0xCD   -- reserved --
	{"",Qt::Key_unknown},    // 206   0xCE   -- reserved --
	{"",Qt::Key_unknown},    // 207   0xCF   -- reserved --
	{"",Qt::Key_unknown},    // 208   0xD0   -- reserved --
	{"",Qt::Key_unknown},    // 209   0xD1   -- reserved --
	{"",Qt::Key_unknown},    // 210   0xD2   -- reserved --
	{"",Qt::Key_unknown},    // 211   0xD3   -- reserved --
	{"",Qt::Key_unknown},    // 212   0xD4   -- reserved --
	{"",Qt::Key_unknown},    // 213   0xD5   -- reserved --
	{"",Qt::Key_unknown},    // 214   0xD6   -- reserved --
	{"",Qt::Key_unknown},    // 215   0xD7   -- reserved --
	{"",Qt::Key_unknown},    // 216   0xD8   -- unassigned --
	{"",Qt::Key_unknown},    // 217   0xD9   -- unassigned --
	{"",Qt::Key_unknown},    // 218   0xDA   -- unassigned --
	{"",0},                  // 219   0xDB   VK_OEM_4            | '[{' for US
	{"",0},                  // 220   0xDC   VK_OEM_5            | '\|' for US
	{"",0},                  // 221   0xDD   VK_OEM_6            | ']}' for US
	{"",0},                  // 222   0xDE   VK_OEM_7            | ''"' for US
	{"",0},                  // 223   0xDF   VK_OEM_8
	{"",Qt::Key_unknown},    // 224   0xE0   -- reserved --
	{"",Qt::Key_unknown},    // 225   0xE1   VK_OEM_AX           | 'AX' key on Japanese AX kbd
	{"",Qt::Key_unknown},    // 226   0xE2   VK_OEM_102          | "<>" or "\|" on RT 102-key kbd
	{"",Qt::Key_unknown},    // 227   0xE3   VK_ICO_HELP         | Help key on ICO
	{"",Qt::Key_unknown},    // 228   0xE4   VK_ICO_00           | 00 key on ICO
	{"",Qt::Key_unknown},    // 229   0xE5   VK_PROCESSKEY       | IME Process key
	{"",Qt::Key_unknown},    // 230   0xE6   VK_ICO_CLEAR        |
	{"",Qt::Key_unknown},    // 231   0xE7   VK_PACKET           | Unicode char as keystrokes
	{"",Qt::Key_unknown},    // 232   0xE8   -- unassigned --
	// Nokia/Ericsson definitions ---------------
	{"",Qt::Key_unknown},    // 233   0xE9   VK_OEM_RESET
	{"",Qt::Key_unknown},    // 234   0xEA   VK_OEM_JUMP
	{"",Qt::Key_unknown},    // 235   0xEB   VK_OEM_PA1
	{"",Qt::Key_unknown},    // 236   0xEC   VK_OEM_PA2
	{"",Qt::Key_unknown},    // 237   0xED   VK_OEM_PA3
	{"",Qt::Key_unknown},    // 238   0xEE   VK_OEM_WSCTRL
	{"",Qt::Key_unknown},    // 239   0xEF   VK_OEM_CUSEL
	{"",Qt::Key_unknown},    // 240   0xF0   VK_OEM_ATTN
	{"",Qt::Key_unknown},    // 241   0xF1   VK_OEM_FINISH
	{"",Qt::Key_unknown},    // 242   0xF2   VK_OEM_COPY
	{"",Qt::Key_unknown},    // 243   0xF3   VK_OEM_AUTO
	{"",Qt::Key_unknown},    // 244   0xF4   VK_OEM_ENLW
	{"",Qt::Key_unknown},    // 245   0xF5   VK_OEM_BACKTAB
	{"",Qt::Key_unknown},    // 246   0xF6   VK_ATTN             | Attn key
	{"",Qt::Key_unknown},    // 247   0xF7   VK_CRSEL            | CrSel key
	{"",Qt::Key_unknown},    // 248   0xF8   VK_EXSEL            | ExSel key
	{"",Qt::Key_unknown},    // 249   0xF9   VK_EREOF            | Erase EOF key
	{"",Qt::Key_Play},       // 250   0xFA   VK_PLAY             | Play key
	{"",Qt::Key_Zoom},       // 251   0xFB   VK_ZOOM             | Zoom key
	{"",Qt::Key_unknown},    // 252   0xFC   VK_NONAME           | Reserved
	{"",Qt::Key_unknown},    // 253   0xFD   VK_PA1              | PA1 key
	{"",Qt::Key_Clear}     // 254   0xFE   VK_OEM_CLEAR        | Clear key
};

static const uint CmdTbl[] = { // Multimedia keys mapping table
	// Dec |  Hex | AppCommand
	Qt::Key_unknown,        //   0   0x00
	Qt::Key_Back,           //   1   0x01   APPCOMMAND_BROWSER_BACKWARD
	Qt::Key_Forward,        //   2   0x02   APPCOMMAND_BROWSER_FORWARD
	Qt::Key_Refresh,        //   3   0x03   APPCOMMAND_BROWSER_REFRESH
	Qt::Key_Stop,           //   4   0x04   APPCOMMAND_BROWSER_STOP
	Qt::Key_Search,         //   5   0x05   APPCOMMAND_BROWSER_SEARCH
	Qt::Key_Favorites,      //   6   0x06   APPCOMMAND_BROWSER_FAVORITES
	Qt::Key_Home,           //   7   0x07   APPCOMMAND_BROWSER_HOME
	Qt::Key_VolumeMute,     //   8   0x08   APPCOMMAND_VOLUME_MUTE
	Qt::Key_VolumeDown,     //   9   0x09   APPCOMMAND_VOLUME_DOWN
	Qt::Key_VolumeUp,       //  10   0x0a   APPCOMMAND_VOLUME_UP
	Qt::Key_MediaNext,      //  11   0x0b   APPCOMMAND_MEDIA_NEXTTRACK
	Qt::Key_MediaPrevious,  //  12   0x0c   APPCOMMAND_MEDIA_PREVIOUSTRACK
	Qt::Key_MediaStop,      //  13   0x0d   APPCOMMAND_MEDIA_STOP
	Qt::Key_MediaTogglePlayPause,   //  14   0x0e   APPCOMMAND_MEDIA_PLAYPAUSE
	Qt::Key_LaunchMail,     //  15   0x0f   APPCOMMAND_LAUNCH_MAIL
	Qt::Key_LaunchMedia,    //  16   0x10   APPCOMMAND_LAUNCH_MEDIA_SELECT
	Qt::Key_Launch0,        //  17   0x11   APPCOMMAND_LAUNCH_APP1
	Qt::Key_Launch1,        //  18   0x12   APPCOMMAND_LAUNCH_APP2
	Qt::Key_BassDown,       //  19   0x13   APPCOMMAND_BASS_DOWN
	Qt::Key_BassBoost,      //  20   0x14   APPCOMMAND_BASS_BOOST
	Qt::Key_BassUp,         //  21   0x15   APPCOMMAND_BASS_UP
	Qt::Key_TrebleDown,     //  22   0x16   APPCOMMAND_TREBLE_DOWN
	Qt::Key_TrebleUp,       //  23   0x17   APPCOMMAND_TREBLE_UP
	Qt::Key_MicMute,        //  24   0x18   APPCOMMAND_MICROPHONE_VOLUME_MUTE
	Qt::Key_MicVolumeDown,  //  25   0x19   APPCOMMAND_MICROPHONE_VOLUME_DOWN
	Qt::Key_MicVolumeUp,    //  26   0x1a   APPCOMMAND_MICROPHONE_VOLUME_UP
	Qt::Key_Help,           //  27   0x1b   APPCOMMAND_HELP
	Qt::Key_Find,           //  28   0x1c   APPCOMMAND_FIND
	Qt::Key_New,            //  29   0x1d   APPCOMMAND_NEW
	Qt::Key_Open,           //  30   0x1e   APPCOMMAND_OPEN
	Qt::Key_Close,          //  31   0x1f   APPCOMMAND_CLOSE
	Qt::Key_Save,           //  32   0x20   APPCOMMAND_SAVE
	Qt::Key_Printer,        //  33   0x21   APPCOMMAND_PRINT
	Qt::Key_Undo,           //  34   0x22   APPCOMMAND_UNDO
	Qt::Key_Redo,           //  35   0x23   APPCOMMAND_REDO
	Qt::Key_Copy,           //  36   0x24   APPCOMMAND_COPY
	Qt::Key_Cut,            //  37   0x25   APPCOMMAND_CUT
	Qt::Key_Paste,          //  38   0x26   APPCOMMAND_PASTE
	Qt::Key_Reply,          //  39   0x27   APPCOMMAND_REPLY_TO_MAIL
	Qt::Key_MailForward,    //  40   0x28   APPCOMMAND_FORWARD_MAIL
	Qt::Key_Send,           //  41   0x29   APPCOMMAND_SEND_MAIL
	Qt::Key_Spell,          //  42   0x2a   APPCOMMAND_SPELL_CHECK
	Qt::Key_unknown,        //  43   0x2b   APPCOMMAND_DICTATE_OR_COMMAND_CONTROL_TOGGLE
	Qt::Key_unknown,        //  44   0x2c   APPCOMMAND_MIC_ON_OFF_TOGGLE
	Qt::Key_unknown,        //  45   0x2d   APPCOMMAND_CORRECTION_LIST
	Qt::Key_MediaPlay,      //  46   0x2e   APPCOMMAND_MEDIA_PLAY
	Qt::Key_MediaPause,     //  47   0x2f   APPCOMMAND_MEDIA_PAUSE
	Qt::Key_MediaRecord,    //  48   0x30   APPCOMMAND_MEDIA_RECORD
	Qt::Key_AudioForward,   //  49   0x31   APPCOMMAND_MEDIA_FAST_FORWARD
	Qt::Key_AudioRewind,    //  50   0x32   APPCOMMAND_MEDIA_REWIND
	Qt::Key_ChannelDown,    //  51   0x33   APPCOMMAND_MEDIA_CHANNEL_DOWN
	Qt::Key_ChannelUp       //  52   0x34   APPCOMMAND_MEDIA_CHANNEL_UP
};

#include "SystemInputHook_Windows.h"

unsigned char kbdBuffer[256]; 
Qt::KeyboardModifiers modifiers;
Qt::MouseButtons buttons;

void queryKeyboardModifiers()
{
	modifiers = Qt::NoModifier;
	if (GetKeyState(VK_SHIFT) < 0) {
		kbdBuffer[VK_SHIFT] = 1;
		modifiers |= Qt::ShiftModifier;
	}
	else {
		kbdBuffer[VK_SHIFT] = 0;
	}
	if (GetKeyState(VK_CONTROL) < 0) {
		kbdBuffer[VK_CONTROL] = 1;
		modifiers |= Qt::ControlModifier;
	}
	else {
		kbdBuffer[VK_CONTROL] = 0;
	}
	if (GetKeyState(VK_MENU) < 0) {
		kbdBuffer[VK_MENU] = 1;
		modifiers |= Qt::AltModifier;
	}
	else {
		kbdBuffer[VK_MENU] = 0;
	}
	if (GetKeyState(VK_LWIN) < 0){
		kbdBuffer[VK_LWIN] = 1;
		modifiers |= Qt::MetaModifier;
	}
	else {
		kbdBuffer[VK_LWIN] = 0;
	}
	if (GetKeyState(VK_RWIN) < 0) {
		kbdBuffer[VK_RWIN] = 1;
		modifiers |= Qt::MetaModifier;
	}
	else {
		kbdBuffer[VK_RWIN] = 0;
	}
}

LRESULT CALLBACK WindowsKeyboardHookCallback(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HC_ACTION) {
		QEvent::Type type;
		if (wParam == WM_KEYDOWN || wParam == WM_IME_KEYDOWN || wParam == WM_SYSKEYDOWN)
			type = QEvent::KeyPress;
		else if (wParam == WM_KEYUP|| wParam == WM_IME_KEYUP || wParam == WM_SYSKEYUP) 
			type = QEvent::KeyRelease;
		else
			return CallNextHookEx(NULL, nCode, wParam, lParam);
		queryKeyboardModifiers();
		PKBDLLHOOKSTRUCT windowsKeyboard = (PKBDLLHOOKSTRUCT)lParam;
		qint64 timestamp = QDateTime::currentDateTime().toMSecsSinceEpoch();
		MinimizedInputEvent_Keyboard keyEvent{ type, timestamp, windowsKeyboard->vkCode, modifiers };
		Q_EMIT SystemInputHook::Instance()->invokeKeyboardEvent(keyEvent);
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

LRESULT CALLBACK WindowsMouseHookCallback(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode == HC_ACTION){
		QEvent::Type type = QEvent::Type::None;
		Qt::MouseButton button = Qt::NoButton;
		qint32 delta = 0;
		PMSLLHOOKSTRUCT windowsMouse = (PMSLLHOOKSTRUCT)lParam;
		switch (wParam) {
		case WM_MOUSEMOVE:
			type = QEvent::MouseMove; button = Qt::NoButton; break;
		case WM_LBUTTONDOWN:
			type = QEvent::MouseButtonPress; button = Qt::LeftButton; break;
		case WM_LBUTTONUP:
			type = QEvent::MouseButtonRelease; button = Qt::LeftButton; break;
		case WM_LBUTTONDBLCLK: // Qt QPA does not handle double clicks; button = send as press
			type = QEvent::MouseButtonPress; button = Qt::LeftButton; break;
		case WM_MBUTTONDOWN:
			type = QEvent::MouseButtonPress; button = Qt::MiddleButton; break;
		case WM_MBUTTONUP:
			type = QEvent::MouseButtonRelease; button = Qt::MiddleButton; break;
		case WM_MBUTTONDBLCLK:
			type = QEvent::MouseButtonPress; button = Qt::MiddleButton; break;
		case WM_RBUTTONDOWN:
			type = QEvent::MouseButtonPress; button = Qt::RightButton; break;
		case WM_RBUTTONUP:
			type = QEvent::MouseButtonRelease; button = Qt::RightButton; break;
		case WM_RBUTTONDBLCLK:
			type = QEvent::MouseButtonPress; button = Qt::RightButton; break;
		//case WM_XBUTTONDOWN:
		//	type = QEvent::MouseButtonPress; button = extraButton(msg.wParam); break;
		//case WM_XBUTTONUP:
		//	type = QEvent::MouseButtonRelease; button = extraButton(msg.wParam); break;
		//case WM_XBUTTONDBLCLK:
		//	type = QEvent::MouseButtonPress; button = extraButton(msg.wParam); break;
		case WM_NCMOUSEMOVE:
			type = QEvent::NonClientAreaMouseMove; button = Qt::NoButton; break;
		case WM_NCLBUTTONDOWN:
			type = QEvent::NonClientAreaMouseButtonPress; button = Qt::LeftButton; break;
		case WM_NCLBUTTONUP:
			type = QEvent::NonClientAreaMouseButtonRelease; button = Qt::LeftButton; break;
		case WM_NCLBUTTONDBLCLK:
			type = QEvent::NonClientAreaMouseButtonPress; button = Qt::LeftButton; break;
		case WM_NCMBUTTONDOWN:
			type = QEvent::NonClientAreaMouseButtonPress; button = Qt::MiddleButton; break;
		case WM_NCMBUTTONUP:
			type = QEvent::NonClientAreaMouseButtonRelease; button = Qt::MiddleButton; break;
		case WM_NCMBUTTONDBLCLK:
			type = QEvent::NonClientAreaMouseButtonPress; button = Qt::MiddleButton; break;
		case WM_NCRBUTTONDOWN:
			type = QEvent::NonClientAreaMouseButtonPress; button = Qt::RightButton; break;
		case WM_NCRBUTTONUP:
			type = QEvent::NonClientAreaMouseButtonRelease; button = Qt::RightButton; break;
		case WM_NCRBUTTONDBLCLK:
			type = QEvent::NonClientAreaMouseButtonPress; button = Qt::RightButton; break;
		case WM_MOUSEWHEEL:
		case WM_MOUSEHWHEEL:
			delta = (SHORT)HIWORD(windowsMouse->mouseData); type = QEvent::Wheel; button = Qt::MiddleButton; break;
		default: // WM_MOUSELEAVE
			break;
			return CallNextHookEx(NULL, nCode, wParam, lParam);
		}
		if (type == QEvent::MouseButtonPress || type == QEvent::NonClientAreaMouseButtonPress) {
			buttons |= button;
		}
		else if (type == QEvent::MouseButtonRelease|| type == QEvent::NonClientAreaMouseButtonRelease) {
			buttons &= (~button);
		}
		qint64 timestamp = QDateTime::currentDateTime().toMSecsSinceEpoch();
		MinimizedInputEvent_Mouse mouseEvent{ type ,timestamp, button, QPoint(windowsMouse->pt.x, windowsMouse->pt.y), delta };
		Q_EMIT SystemInputHook::Instance()->invokeMouseEvent(mouseEvent);
	}
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}

SystemInputHook_Windows::SystemInputHook_Windows()
{

}

void SystemInputHook_Windows::startup(KeyboardEventCallback keyboardCallback, MouseEventCallback mouseCallback)
{
	SystemInputHook::startup(keyboardCallback, mouseCallback);
	mKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, WindowsKeyboardHookCallback, GetModuleHandle(NULL), NULL);
	if (!mKeyboardHook) {
		qFatal() << "[!] Failed to get keyboard hook handle from SetWindowsHookEx()";
	}

	mMouseHook = SetWindowsHookEx(WH_MOUSE_LL, WindowsMouseHookCallback, NULL, 0);
	if (!mMouseHook) {
		qFatal() << "[!] Failed to get mouse hook handle from SetWindowsHookEx()";
	}
}

void SystemInputHook_Windows::shutdown()
{
	UnhookWindowsHookEx(mKeyboardHook);
	UnhookWindowsHookEx(mMouseHook);
}

#endif
