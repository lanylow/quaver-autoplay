# Quaver Autoplay
An internal autoplayer for [Quaver](https://store.steampowered.com/app/980610/Quaver/) that works on both 4-key and 7-key game modes.

## How to use
First, you will have to set your keybinds so the autoplayer knows which keys to click. Open `inc/autoplayer/autoplayer.hpp` and change values in `key_config` according to [the list of key codes](https://learn.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes). After that, you can compile the program and inject it into `Quaver.exe`, from there it will work automatically.

## Disclaimer
Detection status of this program is unknown, and it's probably going to stay that way. This project was made for fun and I do not recommend using this while connected to Quaver's servers, as it will most likely get you banned. That said, you can use this offline with no risk.
