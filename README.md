# Neuro

Крч, простая нейросеть. Обучается на алгоритме back propagation. Работает медленно, но **РАБОТАЕТ**
Файлы конфигов старые, сейчас сеть работает лучше, поэтому их лучше перегенить

## Интерфейс

```CPP

network net(std::vector<int>()); //Создает сеть с заданной топологией
net.feed(std::vector<double>()); //Заполняет входной слой данными
net.run(); -> std::vector<double>(); //Считает выходной слой и его же возвращяет
net.save('test.lol') //Сохраняет текущую конфигурацию сети
static network::load('test.lol') -> network // восстанавливает сеть из файла (пока не работает)

```

Вот и все, вот так просто. Писать на английском очень лень, сори. Потетсти сеть и напиши в issue как тебе.
