# termraria

![screenshot](https://github.com/OtryvnoyKalendar/termraria/blob/main/screenshots/screenshot%202.png)

### Общее описание
Termraria - это консольная игра песочница, которая работает в Linux. Это только прототип игры, которую я написал для практики языка C.
Игра сделана на основе видео с ютуб канала Begin End и адаптирована под Linux. Вот *ссылки на видео*:  
[Язык Си с нуля - Урок 59 - симулятор воды и песка](https://www.youtube.com/watch?v=-131tBG9dZY&list=PLBOPkQsFLCR2DWRY74L03FmbRtz_Yy73_&index=60),  
[Язык Си с нуля - Урок 61 - Симулятор Террарии.](https://www.youtube.com/watch?v=XkASqnVkzp8&list=PLBOPkQsFLCR2DWRY74L03FmbRtz_Yy73_&index=62).

### Как играть
Чтобы начать играть, нужно открыть консоль и перейти в папку с проектом. Дальше просто выполните скрипт:
```sh
sh project_start
```

- Управление:  
'ESC' - выйти из игры  
'1' - песок  
'2' - вода  
'3' - стена  
'4' - пустота  
'ЛКМ'/'ПКМ' - поставить материал  
'R' - перезапустить карту  
'W' - вверх  
'A' - влево  
'S' - вниз  
'D' - вправо  
'колёсико мыши вверх'+'ЛКМ' - увеличить радиус  
'колёсико мыши вниз'+'ЛКМ' - уменьшить радиус  

Если вы хотите **изменить код игры**, то вам не нужно ничего перекомпелировать и удалять вручную. После внесения изменений в файлы игры, просто снова запустите скрипт `project_start`, он всё сделает за вас.

Если вы захотите воспользоваться **отладчиком GDB**, чтобы дебажить код, то скрипт нужно запускать так:
```sh
sh project_start gdb
```
Этот скрипт создаст отдельный терминал с отладчиком и присоединиться к процессу игры.
