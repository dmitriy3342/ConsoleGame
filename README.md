# ConsoleGame

//Считывание клавиатуры
//https://docs.microsoft.com/ru-ru/windows/desktop/inputdev/virtual-key-codes
```c++
short keyState = GetKeyState(key);
bool isToggled = keyState & 1;
bool isDown = keyState & 0x8000;
```