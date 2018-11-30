# replicaJunction QMK layouts

An example implementation of the [QMK docker bootstrap](https://github.com/replicaJunction/qmk_docker_bootstrap) which contains replicaJunction's keymap files.

## Features

### Tap-dance layer toggle

My Escape key also serves as a layer toggle:

* 1 tap sends an Escape keypress, and also acts as an emergency "halp I'm lost" button by disabling any persistent layers
* 2 taps turns on my number pad layer
* 3 taps turns on a QWERTY layer, which can be used for gaming
* 5 or more taps resets the keyboard

### Extend Layer

[Originally found on the Colemak forums](https://forum.colemak.com/topic/2014-extend-extra-extreme/), having a QMK-powered keyboard allows a super easy implementation of this concept. The idea is to place commonly-used keys under easy reach of your hands. Since I work with text often, my most common needs are things like Ctrl+Shift+arrow keys, and they're easy to access using this layer. (While technically it's four keypresses instead of just three, since it takes one key to enter the layer, that one key is a thumb button and the other three are all on the home row, so I find it much more comfortable than modifiers on a traditional keyboard.)

Also featured in this layer is easy access to Tab, plus a Shift+Tab key. Alt-Tabbing back and forth, along with Ctrl-Tab, are super easy and friendly. When I need Ctrl+Alt+Delete, I typically use the ones found on this layer.

### Vim emulation

Based heavily on the work by [xtonhasxim](https://github.com/qmk/qmk_firmware/tree/master/users/xtonhasvim), this allows the use of Vim-like navigation and simple editing in other applications.

These keymaps are for Windows (tested on Windows 10). I've tried to isolate some of the OS-specific stuff into defines, but it would take some work to translate this to another OS. However, xtonhasvim originally wrote his copy for Mac OS, so see his work for a better implementation on Mac.

To be clear, not much is supported other than basic navigation and motions. QMK doesn't have any awareness of what text is in the application - all it can do is send keyboard shortcuts. That said, I still find this more useful than nothing at all when Vim or a Vim editor plugin isn't available.

## Credits

* [Drashna](https://github.com/qmk/qmk_firmware/blob/master/users/drashna/readme.md)
  * User / keymap function ideas
* [Jeremy](https://github.com/qmk/qmk_firmware/blob/master/keyboards/atreus/keymaps/jeremy/readme.md)
  * Sanity check on the Function keys (_of course they should be in rows of 4, not rows of 3 like a number pad. Why did I ever use anything else?_)
* [DreymaR of the Colemak forums](https://forum.colemak.com/topic/2014-extend-extra-extreme/)
  * Original idea of the Extend layer
* [xtonhasvim](https://github.com/qmk/qmk_firmware/tree/master/users/xtonhasvim)
  * Vim emulation - original idea and basic state machine concept
