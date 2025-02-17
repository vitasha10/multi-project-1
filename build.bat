@echo off
setlocal EnableDelayedExpansion

:: --- Настройки скрипта ---
:: Тип генератора для CMake
set BUILD_TYPE=Ninja
:: Суффикс для имени папки сборки
set BUILD_SUFFIX=ninja

:: Каталоги сборки и исходников
set BUILD_FOLDER=build_%BUILD_SUFFIX%
set SOURCE_FOLDER=..

:: Запись логов в файл
set LOG_FILE=build.log

:: Кодировка UTF-8 для корректного отображения символов
chcp 65001 > nul

:: --- Проверка наличия CMake ---
where cmake > nul 2>&1
if errorlevel 1 (
    echo Ошибка: CMake не найден. Убедитесь, что CMake установлен и доступен в PATH.
    exit /b 1
)

:: --- Работа с аргументами ---
:: Установим тип сборки (по умолчанию Release)
set CONFIG=Release
if "%1"=="" goto skip_args
if "%1"=="clean" (
    if not "%2"=="" (
        echo Ошибка: Команда "clean" не принимает дополнительных аргументов.
        exit /b 1
    )
    echo Очистка папки сборки...
    rmdir /S /Q %BUILD_FOLDER%
    exit /b
)
if "%1"=="debug" set CONFIG=Debug
if "%1"=="release" set CONFIG=Release
:skip_args

echo Тип сборки: %CONFIG%

:: --- Проверка существования папки сборки ---
if not exist %BUILD_FOLDER% (
    echo Создаём папку сборки: %BUILD_FOLDER%
    mkdir %BUILD_FOLDER%
)

:: Сохраняем текущую директорию
set START_DIR=%cd%

:: Переходим в папку сборки
cd %BUILD_FOLDER%

:: --- Генерация файлов сборки ---
echo Генерация файлов сборки...
cmake -G %BUILD_TYPE% -DCMAKE_BUILD_TYPE=%CONFIG% %SOURCE_FOLDER% > %LOG_FILE% 2>&1
if errorlevel 1 (
    echo Ошибка: Генерация файлов сборки не удалась. См. %LOG_FILE% для подробностей.
    cd %START_DIR%
    exit /b 1
)

:: --- Запуск сборки ---
echo Запуск сборки...
cmake --build . >> %LOG_FILE% 2>&1
if errorlevel 1 (
    echo Ошибка: Сборка не удалась. См. %LOG_FILE% для подробностей.
    cd %START_DIR%
    exit /b 1
)

:: Возвращаемся в исходную директорию
cd %START_DIR%
echo Сборка успешно завершена. См. %LOG_FILE% для подробностей.