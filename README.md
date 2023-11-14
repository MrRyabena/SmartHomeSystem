# SmartHomeSystem

<pre>
   _____                      _     _    _                         _____           _                   
  / ____|                    | |   | |  | |                       / ____|         | |                  
 | (___  _ __ ___   __ _ _ __| |_  | |__| | ___  _ __ ___   ___  | (___  _   _ ___| |_ ___ _ __ ___    
  \___ \| '_ ` _ \ / _` | '__| __| |  __  |/ _ \| '_ ` _ \ / _ \  \___ \| | | / __| __/ _ \ '_ ` _ \   
  ____) | | | | | | (_| | |  | |_  | |  | | (_) | | | | | |  __/  ____) | |_| \__ \ ||  __/ | | | | |  
 |_____/|_| |_| |_|\__,_|_|   \__| |_|  |_|\___/|_| |_| |_|\___| |_____/ \__, |___/\__\___|_| |_| |_|  
                                                                          __/ |                      
                                                                         |___/                       

</pre>

# Содержание
 - [Структура проекта]()
 - [1. Введение](#introduction)
 - [2. Цели](#purposes)
 - [3. Подход к проектированию системы](#design_approach)
 - [4. Задачи](#tasks)
 - [5. Выбор компонентов](#choice)




<a id="introduction"></a>
# Введение
Мы живем в эпоху кремниевой лихорадки, когда на каждом шагу нас окружает огромное количество высокотехнологичных устройств с микрочипами внутри. Даже самые обыденные бытовые приборы, такие как электрочайник, светодиодная лампочка или обогреватель, оказываются оборудованы умными мозгами, превращая наши дома в настоящие технологические чудеса. Чего уж там говорить про различные смартфоны, компьютеры, серверы... Такая распространенность микроэлетроники привела к росту технологий и увеличению масштабов производства. Появилось много микросхем, доступных обычным радиолюбителям. Сейчас, всего за цену одной порции шаурмы можно заказать из Поднебесной модуль, способный решать задачи с эффективностью компьютера на i486 (процессор Intel 80486, 1989г), при этом сам он поместится в чайной ложке!<br>

Системой умного дома сейчас уже мало кого можно удивить. На рынке представлены промышленные решения от именитых брендов. Компании готовы спроектировать и построить дом под любые запросы, либо предоставляют линейку модулей, соединяя которые можно собрать кастомную систему самому. Для таких продвинутых решений не нужны знания программирования и инженерии, все уже продумано разработчиками, требуется только подключить модули согласно инструкции и настроить их взаимодействие в удобном приложении. Линейки модулей достаточно обширные и позволяют контролировать температуру, освещение, включать и выключать приборы по расписанию, общаться с помощью чат-ботов и голосовых помощников и многое другое.<br>

### А зачем это надо?
Глядя на все это разнообразие может показаться что создавать еще одну такую систему совершенно бессмысленно, однако все не так однозначно. Так какие же плюсы заниматься самостоятельной разработкой?
- Цена. Готовые модули стоят достаточно дорого и собрать на них полноценную систему выйдет далеко не дешево.
- Функциональность. Индивидуальная разработка позволяет реализовать все полностью под себя, вывести доступ к любым настройкам и иметь возможность в любой момент исправить или модернизировать систему.
- Опыт. Во время разработки потребуется изучение программирования на низком и высоком уровне, изучение радиоэлектроники, создание электронных схем и плат, пайка, 3D-моделирование и печать (в данном проекте не используется, но ничто не мешает добавить) и пр.
- Возможность наладить коммерческое производство.
- Иметь за спиной достаточно объемный проект.
- В системе собраны алгоритмы, применение которым можно найти в других разнообразных проектах.

Да, такие мысли приходили в голову многим и аналогичных проектов с подробными статьями много на просторах интернета. Все они достаточно разнообразны и написаны, в основном, под конкретную ситуацию. Этот проект не является исключением — на выходе получается конкретная система умного дома, но, основу проекта составляет библиотека, которая позволяет реализовать систему "под любой дом". Поэтому правильнее будет сказать, что _проект заключается в разработке единого метода реализации системы умного дома, а действительно существующая система — это всего лишь пример применения разработки на практике._


### Принцип работы
Все много раз слышали, что в электронике все работает по принципу нулей и единиц (Булева алгебра), где сами значения "0" и "1" — очень абстрактные понятия "нет сигнала" и "есть сигнал". Чтобы понять как на этом построить умный дом, надо копнуть чуть поглубже. Рассмотрим упрощенную версию какого-нибудь модуля. <br>

![](schemes/Attiny13_e)

Первое что нужно — это подать на схему питание. Линий питания две:
- **COM (GND, VSS, земля)** — общий вывод питания, относительно него измеряются все остальные потенциалы в схеме.
- **+V (VСС, VIN)** — положительная линия питания, их может быть несколько, рассчитанных на разные напряжения, например, +12V, +5V, +3.3V. Еще бывает отрицательное напряжение (относительно GND, опять же), но с ним обычно работают усилители и компараторы, в большинстве архитектур ЭВМ для основных логических цепей оно не применяется.

Вторая часть схемы, которая будет управлять модулем это какая-то логическая схема. Наш дом — умный, поэтому схема будет не простая. Собрать самому такую, используя лишь базовые компоненты (резисторы, транзисторы, диоды...) крайне сложно, объемно и не рационально, да к тому же работать стабильно она вряд ли будет. К счастью, за нас проблему уже давно решили и все необходимые цепи собраны в одном небольшом радиокомпоненте — микросхеме. <br>**Интегральная схема (микросхема)** — это электронная схема, помещенная на полупроводниковой (чаще всего кремниевой) подложке, с помощью фотолитографии. Так, небольшой корпус может содержать внутри как простой набор логических элементов, так и целый процессор или контроллер, последний из которых нам и нужен.<br>
**Микроконтроллер** — это микросхема, которая содержит в себе процессор, ОЗУ, ПЗУ и периферийные устройства. Это целый небольшой компьютер, который может выполнять математические операции и управлять другими устройствами с помощью периферии.<br>
Чтобы микроконтроллер мог принимать и выводить какие-то сигналы он оснащен выводами (контактами, пинами) с интерфейсом GPIO (general-purpose input/output). Такие пины могут работать в двух режимах: INPUT (вход) и OUTPUT (вывод);
- В режиме INPUT микроконтроллер сравнивает входящий сигнал с землей (GND) и принимает его за 1, если его потенциал больше GND. 
- Аналогично в режиме OUTPUT микроконтроллер может формировать на определенном контакте 0 или потенциал, равный его напряжению питания. <br>

Теперь логический сигнал от микроконтроллера надо усилить с помощью транзистора или реле и можно управлять нагрузками (светом, отоплением, чайником...) в режиме вкл/выкл. Для того, чтобы управлять интенсивностью (мощностью) нагрузки (т.е. яркостью света, температурой нагревателя) необходимо регулировать подаваемое на них напряжение. В цифровой электронике для этого применяется ШИМ (PWM). Говоря по-простому, микроконтроллер очень быстро включает и выключает нагрузку на разные микропромежутки времени, а за счет ее инертности получается плавное регулирование.<br>
Выше был описан принцип работы цифровой электроники, но в арсенале многих микроконтроллеров есть блоки аналоговой электроники — АЦП и ЦАП. <br>
- **Аналого-цифровой преобразователь** позволяет микроконтроллеру измерять потенциал входного сигнала в диапазоне от 0, до опорного напряжения (либо задается от отдельного источника, либо совпадает с напряжением питания микроконтроллера) с некоторой точностью, которая зависит от разрядности АЦП. Он используется для считывания информации с датчиков, которые за счет физических эффектов (фотоэффектов, термоэффектов, эффекта Холла и пр.) изменяют напряжение на своем выходе. (Прим. цифровые датчики имеют встроенный АЦП и микроконтроллер для передачи информации по интерфейсам связи). <br>
- **Цифро-аналоговый преобразователь позволяет** изменять потенциал сигнала в некотором диапазоне, он обычно служит для звуковых сигналов либо в качестве "цифровых потенциометров".

### Let's go!
Теперь, вдохновившись идеей и поняв принцип работы, можно пробовать создавать свою систему. На одной теории дом не построишь, поэтому разработка требует постоянных экспериментов, которые подробно описаны в основной части документации.



<a id="purposes"></a>
# Цели

Немного выше мы уже рассмотрели, как можно создать простой модуль, который автоматизирует какой-нибудь процесс. Остается создать еще несколько таких модулей, объединить их в одну систему и... Возникает вопрос: а что такое система умного дома? Какой у нее должен быть функционал? Понятие очень обширное, поэтому стоит сразу определить что конкретно должно получиться. </br>
Первое что приходит в голову, когда речь идет об автоматизации — это различное ругилирование температуры, включение/выключение света, регулирование работы бытовых приборов и прочее. Задач много, они могут быть разнообразны, но все сводятся к тому, что нужен какой-то модуль, который будет управлять подключенными к нему ресурсами, при этом сам получать информацию с каких-либо датчиков или напрямую от пользователя, обрабатывать ее и регулировать выходной сигнал. </br>
Звучит все красиво, удобно и функционально, но попользовавшись такой сборкой некоторое время можно сделать вывод типа: если включение света сделать не через выключатель, а через приложение или чат-бота, или даже по датчику движения, то мы получим все тот же выключатель света, только реагирующий не на физической нажатие, а на посланную команду или срабатывание датчика. В итоге в какой-то момент пользователю надоест постоянно открывать приложение в телефоне, или махать рукой перед датчиком. </br>
Такую систему более правильно назвать не "умной", а "автоматизированной". Она сама реагирует на некоторые события, имеет просты алгоритмы их обработки, но человеку все равно приходится достаточно много вмешиваться и подсказывать системе какой режим сейчас стоит включить. Однако, система автоматизации — необходимый этап при создании полноценного умного дома. Она является основой, и промежуточным результатом. </br>
</br>
Теперь об "умной системе". Чтобы система могла самостоятельно эффективно решать задачи она дложна обладать искуственным интеллектом. Тогда можно смело заявить, что необходимо всего лишь к автоматизированной системе добавить искуственный интеллект — и вот готов "умный дом". Вродебы все хорошо, но в наше время еще не создан полноценынй искуственный интеллект, который бы прошел тест Тьюринга и мог полностью самостятельно развиваться, без чьего либо вмешательства. Впрочем, а нужен ли такой мощный мозг умному дому, да и можно ли будет вообще его заставить что-то делать, ему то это все зачем? Вероятно, ответить на эти вопросы можно будет через пару десятков лет, так что будем использовать доступные реальные варианты. Огромной популярностью сейчас пользуются различные нейросети. Конечно, систему можно связать, например, с chatGPT, но он больше проходит для анализа текста, чем принятия решений. Можно написать свою нейросеть, которая будет заточена именно под управление умным домом. В этом проекте пока реализовывать такие "мозги" не будем, ввиду сложности архитектуры реализации и обучения нейросетей. Все же мозги можно организвать более простыми и не менее эффективными способами. Это позволит сэкономить время на разработку и физические вычислительные ресурсы, кроме того упростит отладку всей системы и повысит стабильность. Отказываться полностью от нейросетей конечно не стоит, ведь уже есть готовые решения, например, для распознания человека в кадре. Поэтому внедрять нейросети имеет смысл в обработку конкретных блоков данных, а не полностью доверять им управление всей системой. </br>
### Выводы 
В итоге получаем, что главной целью является создать автоматическую систему, которая максимально упрощает процессы в домашнем быту, способна саморегулироваться и требует минимального контроля и вмешательства человека. </br>
Кроме того по итогам проекта, мы получаем большую базу материалов для создания систимы умного дома, документацию по использованию и примеры реализации на практике. </br> 
Все это и является проетом **"Smart Home System"**.
### Этапы создания проекта
Цель определена, но для полной картины стоит разбить ее на последовательные задачи со своими промежуточными результами.
- Этап 1. Создание системы автоматизации процессов.
    - Определение устройств и процессов, которые будет контролировать Smart Home System.
    - Физическая реализация модулей, отвечающих за регулирование устройств и процессов.
    - Объединение модулей в единую связанную систему.
- Этап 2. Создание системы взаимодействия с пользователем.
    - Определение методов взаимодействия с пользователем.
    - Релизация методов взаимодействия с пользователем.
    - Разработка дублирующих систем контролирования Smart Home System.
    - Разработка поведения системы при ошибках и критических ситуациях, экстренное уведомление пользователя.
- Этап 3. Проектирование алгоритмов саморегулирования системы.
    - Проектирование инструкций поведения при изменении входных данных.
    - Согласование всех алгоритмов для связанного взаимодействия.
    - Создание сценариев режимов работы системы.
    - Разработка алгоритмов, подбирающих наиболее оптимальный сценарий для текущей ситуации.
    - Разработка продвинутого взаимодействия с пользователем.
- Этап 4. Настройка и отладка Smart Home System.
    - Установка сценариев поведения.
    - Преключение между сценариями.
    - Подбор наиболее эффективных параметров.


<a id="design_approach"></a>
# Подход к проектированию системы
При проектировании нашлось два способа реализации Smart Home System:
1. Создается один большой модуль, который включает в себя несколько микроконтроллеров, их обвязку, систему питания и подключения устройств. Он реализует все необходимые системы.
2. Создается много небольших модулей, каждый из которых контролирует один небольшой блок устройств и процессов, имеет собственную систему питания. Все модули связываюстся между собой по WiFi и образуют единую систему.</br>
Преимущества первого модуля заключаются в удобстве обслуживания: все находится в одном корпусе, не нужно бегать по всему дому чтобы что-то подключить или поправить. При создании такого модуля получается большая печатная плата, на которой расположены несколько микроконтроллеров, вся необходимая им обвязка, силовые цепи и блоки питания. Схема получается очень большая и сложная, возникает много трудностей при пайке и выявлении ошибок. Самая большая проблема — огромное количество проводов, которые необходимо протянуть по всему дому. Они постоянно отовсюду вылезают, мешают, стоят дорого и наводят помехи друг на друга.</br>
Второй способ оказался более практичным. Мы можем постепенно создавать небольшие схемы, добавлять, менять или переделывать их. Сигнальные и силовые линии не нужно тянуть по всему дому, все получается аккуратно и компактно.</br>
Первый способ имеет смысл только для реализации каких-то небольших систем, по типу контроллера теплицы или какого-то небольшого помещения. Поэтому Smart Home System основан на втором способе.

<a id="tasks"></a>
# Задачи
*Выше уже описаны цели и идеи их реализации, здесь речь пойдет более конкретно о задачах, которые можно решить с помощью Smart Home System.*</br>
- Первое что приходит в голову, когда речь идет об умном доме — автоматическое включение и регулировка света. Свет должен включаться, когда это необходимо, выключаться, но только тогда, когда он действительно никому не нужен и плавно регулироваться, постоянно выдерживая одинаковое значение яркости. Еще одна дополнительная функция точно не оставит равнодушными людей, которым приходитя рано втавать — будильник-рассвет — комната плавно заливается теплым светом, эмитирую восход солнца.</br>
Задача достаточно простая и реализуется даже без всяких дополнительных библиотек.
- Если уж речь пошла об освещении, то можно добавить красоты и технологичности — RGB-подсветку. Тут необходимы инструменты для работы с **RGB** (обычные четырезвыводные, где требуется только регалировать яркость каждого канала цвета) и **ARGB** (адресные светодиоды, позволяют управлять цветом каждого светодиода, независимо от всех  остальных) светодиодами. Если первые все еще можно ковырять вручную, то для адресных точно потребуются дополнительные библиотеки. Когда есть хорошие решения, писать заново библиотеки смысла особого нет, поэтому используя готовую основу в виде пары библиотек останется только создать различные эффекты и режимы работы.
- Климат-контроль. Smart Home System в основном следит за 3 параметрами: температурой, уровнем влажности и концентрацией углекислого газа в воздухе. Обрабатывая их, можно настроить регулировку котла или подачи горячей воды, работу увлажнителей воздуха и открывать форточки (или включать систему вентиляции).
- Метеостанция. Измерение температуры, влажности, скорости и направления ветра, атмосферного давления. Обработка результатов и составление прогноза погоды на ближайшее время, рекомендаций по одежде и ожиданий на день.
- Контроллер теплицы. В доме наверняка есть комнатные растения, а может быть целая теплица или сад. Необходимо реализовать автополив, контроль влажности почвы и досвечивание растений.
- IoT. Реализовать возможность получать данные из интернета, выкладывать их, обмениваться с пользователями, различных чат-ботов и прочие прелести Интернета Вещей.


<a id="choice"></a>
# Выбор компонентов
Пора приступать непосредственно к разработке и реализации Smart Home System.</br>
Для управления всеми модулями от микроконтроллеров требуется наличие достаточного количества выводов GPIO, поддержка (желательно аппаратная) интерфейсов UART, I2C, SPI, PWM, WiFi, и встроенный АЦП.</br>
Сейчас на рынке представлено много линеек микроконтроллеров, доступных простым радиолюбителям: 
- Компания Atmel представляет семейства на архитектуре AVR — Attiny и Atmega. Первые микроконтроллеры совсем крохотные и использовать их можно только для небольших задачь, например, управления одним светильником и связи с остальными. Семейство Atmega всем более известно под маркой Arduino, т.к. лежит в основе большинства их плат. Эти камушки уже могут похвастаться большим арсеналом GPIO, АЦП, высоким возможным током с пина. На их основе можно собирать полноценные модули, нехватает только WiFi или другой беспроводной связи.
- Китайцы, в лице Espressif Systems  разработали свою линейку микроконтроллеров с WiFi на борту, flash-памятью и достаточно мощными (для задач умного дома) вычислительными ядрами.
- В сети много гайдов по созданию сервера умного дома на основе Raspberry Pi. Это семейство представляет собой целые миниатюрные компьютеры на архитектуре ARM, позволяющие работать с операционной системой Linux и выводить изображение на монитор. Тема на самом деле достаточно крутая и найти им применение не составит проблем — можно собрать хотя бы домашний сервер и это выйдет компактнее, чем переделавать какой-нибудь старый комп.</br>
Мощности малинки для Smart Home System будут избыточные, да и стоят такие платы достаточно дорого. В итоге выбор пал на 3 основных микроконтроллера: Atmega328P, ESP8266, ESP32.

### ATmega328P
Этот микроконтроллер удобен в использовании, крайне неприхотлив в эксплуатации, имеет много аналоговых пинов, аппаратную поддержку ШИМ.

|Parametr|Value|
|:-:|:-:|
|CPU type|8-bit AVR|
|CPU speed|20 MHz|
|Flash memory|32 KB|
|SRAM|2 KB|
|EEPROM|1 KB|
|I/O pins|23|
|Operating Voltage Range|1.8 — 5.5 V|


![ATmega328P pinout](schemes/Atmega328P-pinout.png)











---
<!-- ![esp32 pinout](schemes/ESP32-VROOM-32D-PINOUT.png) -->
<!-- ![esp8266 pinout](schemes/esp8266-pinout.jpg) -->


