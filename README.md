# Compiler2019
[![Build Status](https://travis-ci.com/catalyst-team/catalyst.svg?branch=master)](https://travis-ci.com/carakanz/Compiler2019)
[![Github contributors](https://img.shields.io/github/contributors/carakanz/Compiler2019.svg?logo=github&logoColor=white)](https://github.com/carakanz/Compiler2019/graphs/contributors)

Пример использования библиотек в папке test.

Билд и запуск тестов: `./scripts/run_all.sh`

Запуск в докер контейнере:

1. Запуск тестов (ubuntu): `(sudo) make docker_tests`
2. Запуск тестов (alpine, lightweight container):
 `(sudo) make docker_tests_light`
3. Запуск терминала, присоединенного к контейнеру с исходным
кодом (ubuntu): `(sudo) make docker_dev`
3. Запуск терминала, присоединенного к контейнеру с исходным
кодом (alpine, lightweight container):
 `(sudo) make docker_dev_light`