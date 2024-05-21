# test_2gis

Реализована консольная программа, принимающая на вход имя файла и набор параметров:
- `test -f <file> -m words -v <mother>`  -  печатает количество слов «mother» в файле «file». \
При этом учитывается регистр и не учитываются знаки препинания. Например, при поиске слова «mother» будут включены в подсчёт «mother's» и «mother,», но не будут учитываться «Mother» и «mothers»;
- `test -f <file> -m checksum`           -  печатает 32-битную чексумму, рассчитанную по алгоритму checksum = word1 + word2 + ... + wordN (word1..wordN –
32-хбитные слова);
- `test -h`                              -  печатает информацию о программе и описание параметров. 

При неправильном введении флагов печатается информация о программе и описание параметров.
При некорректном файле печатается информация об ошибке.

Содержание проекта:

├── CharlesDickens-OliverTwist_68.txt - файл для проверки подсчёта количества слов. В частности, слов «mother» здесь 68 штук; \
├── file_checksum.txt                 - файл для проверки подсчёта чексуммы; \
└──file_little.txt                    - маленький файл для проверки подсчёта количества слов.

Для быстрого запуска можно использовать makefile, применив следующие соманды:
- make words       -  напечатать количество слов;
- make checksum    -  напечатать чексумму;
- make help        -  напечатать информацию о прграмме;
- make incorrect   -  напечатать неправильный пример команды.


