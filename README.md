# Jenkins-Traub methods

Внутри лежит 2 имплементации метода для нахождения корней методом Дженкинса Трауба

## В проекте участвовали:
### КМБО-04-20
- Сыргулев Александр
- Жуков Кирилл
- Репнев Илья
- Столяров Георгий

### КМБО-06-20
- Виктория Коротаева
- Вероника Трушникова


## Инструкция к проекту
### Как запускать

Скачать репозиторий и собрать 
```shell
git clone https://github.com/Sunaked/jenkins_traub.git && cd jenkins_traub && make
```

### Запустить тесты
Из главной директории:
```shell
make test
```
Запустит сборку и запуск тестов в директории tests/

### Запустить бенчмарк (нагрузочное тестирование)
Для запуска нагручного тестирования, т.е. проверки скорости решения полиномов всеми реализациями нужно из главной директории запустить:
```shell
make bench
```


