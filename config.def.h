/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 2;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
static const char *fonts[]          = { "feather:size=11.5", "monospace:size=10" };
static const char col_bg[]          = "#1e1e1e";
static const char col_fg[]          = "#d8dee9";
static const char col_border[]      = "#d4d4d4";
static const char col_alt_bg[]      = "#2e2e2e";
static const char col_alt_fg[]      = "#888888";
static const char *colors[][3]      = {
	/*                  fg          bg          border   */
  [SchemeNorm] =    { col_alt_fg, col_bg,     col_bg },
  [SchemeSel]  =    { col_fg,     col_alt_bg, col_fg },
  [SchemeOcc] =     { col_fg,     col_bg,     col_bg },
  [SchemeInfo]  =   { col_fg,     col_bg,     col_bg },
  [SchemeStatus]  = { col_fg,     col_bg,     col_bg },
};

/* tagging */
static const char *tags[] = {"dev",  "www", "sys", "doc", "vbox", "chat", "mus", "vid", "gfx"};

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class           instance    title    tags mask   isfloating   monitor    float x,y,w,h */
  { "scratchpad",    NULL,       NULL,    0,          1,           -1,        90,  87, 1737, 893 },
  { "Nitrogen",      NULL,       NULL,    0,          1,           -1,        612, 178, 682, 697 },
  { "qalc",          NULL,       NULL,    0,          1,           -1,        617, 334, 680, 292 },
  { "Pavucontrol",   NULL,       NULL,    0,          1,           -1,        670, 216, 544, 597 },
  { "Gucharmap",     NULL,       NULL,    0,          1,           -1,        414, 151, 1111, 801 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 0;    /* 1 means respect size hints in tiled resizals */
static const int lockfullscreen = 1; /* 1 will force focus on the fullscreen window */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "[M]",      monocle },
	{ "[D]",      deck },
	{ "|M|",      centeredmaster },
	{ ">M>",      centeredfloatingmaster },
	{ "|+|",      tatami },
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ NULL,       NULL },
};

/* key definitions */
#include <X11/XF86keysym.h>
#define MODKEY Mod4Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-i", "-p", "run:", NULL };
static const char *termcmd[]  = { "kitty", NULL };
static const char *scratchpad[]  = { "kitty", "--class", "scratchpad", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY,                       XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY|ShiftMask,             XK_Return, spawn,          {.v = scratchpad } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_j,      movestack,      {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_k,      movestack,      {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY|ShiftMask,             XK_m,      zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ Mod1Mask,                     XK_Tab,    shiftview,      {.i = +1} },
	{ Mod1Mask|ShiftMask,           XK_Tab,    shiftview,      {.i = -1} },
	{ MODKEY,                       XK_q,      killclient,     {0} },
  { MODKEY|ShiftMask,             XK_q,      spawn,          SHCMD("kill -9 $(xdotool getwindowpid $(xdotool getwindowfocus))") },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_r,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY|ShiftMask,             XK_f,      fullscreen,     {0} },
	{ MODKEY,                       XK_space,  cyclelayout,    {.i = +1 } },
	{ MODKEY|ShiftMask,	  	        XK_space,  cyclelayout,    {.i = -1 } },
	{ MODKEY,                       XK_f,      togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{ MODKEY|ShiftMask,             XK_r,      quit,           {0} },
  { MODKEY,                       XK_x,                      spawn,    SHCMD("~/.config/scripts/powermenu.sh") },
	{ MODKEY,                       XK_minus, scratchpad_show, {0} },
	{ MODKEY|ShiftMask,             XK_minus, scratchpad_hide, {0} },
	{ MODKEY,                       XK_equal,scratchpad_remove,{0} },
  { 0,                            XF86XK_AudioRaiseVolume,   spawn,    SHCMD("pactl set-sink-volume 0 +5%") },
  { 0,                            XF86XK_AudioLowerVolume,   spawn,    SHCMD("pactl set-sink-volume 0 -5%") },
  { 0,                            XF86XK_AudioMute,          spawn,    SHCMD("pactl set-sink-mute 0 toggle") },
  { 0,                            XF86XK_AudioPlay,          spawn,    SHCMD("playerctl play-pause") },
  { 0,                            XF86XK_AudioStop,          spawn,    SHCMD("playerctl stop") },
  { 0,                            XF86XK_AudioPrev,          spawn,    SHCMD("playerctl previous") },
  { 0,                            XF86XK_AudioNext,          spawn,    SHCMD("playerctl next") },
  { 0,                            XK_Print,                  spawn,    SHCMD("~/.config/scripts/screenshot -f") },
  { ControlMask,                  XK_Print,                  spawn,    SHCMD("~/.config/scripts/screenshot -w") },
  { ShiftMask,                    XK_Print,                  spawn,    SHCMD("~/.config/scripts/screenshot -s") },
};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
  { ClkTagBar,            0,              Button4,        shiftview,  {.i = -1} },
  { ClkTagBar,            0,              Button5,        shiftview,  {.i = +1} },
};

