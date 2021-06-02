<p float="left" align="center">
  <img src="https://raw.githubusercontent.com/parezj/EMBO/master/img/icon.png" alt="EMBO" width="110" />
  &nbsp;&nbsp;&nbsp;&nbsp;
  <a href="https://meas.fel.cvut.cz/" alt="CTU"><img src="https://raw.githubusercontent.com/parezj/EMBO/main/img/ctu_meas_cz.png" /></a>
</p>

# EMBO - EMBedded Oscilloscope
> **[GitHub](https://github.com/parezj/EMBO/releases)**  

Aplikace EMBO se skládá ze 3 primárních přístrojů (4-kanálový osciloskop, logický analyzátor, voltmetr) a ze 3 sekundárních přístrojů (čítač, PWM and funkční generátor). Multiplatformní aplikace je zkompilována pro Windows, Linux a macOS. Stabilní firmware je dostupný pro STM32F103C8, STM32F103RE, STM32F303RE a STM32L412KB ve formátu HEX, další řady budou následovat. Osciloskop EMBO slouží jako levný a jednoduchý nástroj pro hromadnou výuku praktické elektroniky.

Tato práce byla vytvořena v rámci mé diplomové práce na [FEL ČVUT] (https://meas.fel.cvut.cz/) v Praze (Katedra měření) pod vedením doc. Fischera a za pomoci Ing. Hladíka z STMicroelectronics. Chtěl bych jim poděkovat za perfektní podporu. Celý projekt EMBO je zveřejněn pod licencí MIT. 

Ke stažení:
- **[EMBO app 0.1.4 (macOS Catalina)](https://github.com/parezj/EMBO/releases/download/sw0.1.4/EMBO_app-0.1.4_macOS-Catalina.zip)**
- **[EMBO app 0.1.4 (Windows 7/8/10 x64)](https://github.com/parezj/EMBO/releases/download/sw0.1.4/EMBO_app-0.1.4_Win64.zip)**
- **[EMBO app 0.1.4 (Windows 7/8/10 x64 instalátor)](https://github.com/parezj/EMBO/releases/download/sw0.1.4/EMBO_app-0.1.4_Win64_installer.zip)**
- **[EMBO app 0.1.4 (Xubuntu 18)](https://github.com/parezj/EMBO/releases/download/sw0.1.4/EMBO_app-0.1.4_Xubuntu18.zip)**
- **[EMBO firmware 0.2.1](https://github.com/parezj/EMBO/releases/download/fw0.2.1/EMBO_firmware-0.2.1_hex.zip)**

Kapitoly:
1. [Parametry](#1-Parametry)
2. [Připojení](#2-Pripojeni)
3. [Pinout](#3-Pinout)
4. [Popis PC aplikace](#4-Popis-PC-aplikace)
5. [Třídní diagram PC aplikace](#5-Tridni-diagram-PC-aplikace)
6. [Blokové schéma firmware](#6-Blokove-schema-firmware)
7. [Použité IP](#7-Pouzite-IP)

## 1. Parametry

<div align="center" margin="0" padding="0">
<img src="https://raw.githubusercontent.com/parezj/EMBO/master/img/params1.png" alt="EMBO params 1" width="700">
</div>

<div align="center" margin="0" padding="0">
<img src="https://raw.githubusercontent.com/parezj/EMBO/master/img/params2.png" alt="EMBO params 2" width="700">
</div>

## 2. Připojení

<div align="center" margin="0" padding="0">
<img src="https://raw.githubusercontent.com/parezj/EMBO/master/img/comm_types_png_en.png" alt="EMBO comm" width="700">
</div>

## 3. Pinout

### STM32F103C (Blue Pill)

<div align="center" margin="0" padding="0">
<img src="https://raw.githubusercontent.com/parezj/EMBO/master/img/pinout_bluepill_png_en.png" alt="EMBO pinout bluepill" width="500">
</div>

### STM32F303RE (Nucleo-64)

<div align="center" margin="0" padding="0">
<img src="https://raw.githubusercontent.com/parezj/EMBO/master/img/pinout_f303_png_en.png" alt="EMBO pinout F303" width="600">
</div>

## 4. Popis PC aplikace

### Hlavní okno
Po spuštění PC aplikace se uživatel dostane do hlavního okna s výběrem jednotlivých přístrojů. Po levé straně je seznam dostupných portů (v případě OS Windows jsou to COM porty, v případě UNIX-like systému jsou to tty porty). Uživatel vybere port a připojí se k osciloskopu. Zobrazí se tři panely na pravé straně. V horním panelu jsou informace o mikrořadiči a firmware. V prostředním panelu jsou primární přístroje a jejich parametry a ve spodním panelu jsou dostupné sekundární přístroje.

<div align="center" margin="0" padding="0">
<img src="https://raw.githubusercontent.com/parezj/EMBO/master/screenshots/main2.png" alt="EMBO main2" width="700">
</div>

V dolní liště (stavovém panelu) jsou informace o aktuální relaci, které se v ideálním případě aktualizují s periodou 10 ms. Latence udává dobu odezvy osciloskopu a Uptime udává dobu od zapnutí. Pokud je komunikace vytížena (osciloskop odesílá mnoho dat) může se latence zvýšit až na stovky ms v případě použití UART (ST-LINK).

Popis parametrů přístrojů:
- **Fs** — vzorkovací frekvence ve vzorcích za sekundu
- **Mem** — hloubka paměti ve vzorcích
- **Bits** — rozlišení v bitech
- **Mode** —  režim přístroje (4ch 4ADC → 4 kanály na 4 ADC)
- **Port** — přiřazení portů mikrořadiče přístrojovým kanálům (C0 → PC0)
- **Max freq** — maximální frekvence vstupního nebo výstupního signálu

### Osciloskop 
Osciloskop je stěžejní přístroj celého systému. Okno osciloskopu je rozděleno do dvou hlavních bloků. V levém bloku je interaktivní graf, pod kterým leží měřící prvky a ovladače kurzorů. V pravém bloků jsou soustředěny ty nejdůležitější ovládací prvky. Pomocné a doplňkové funkce se ovládají z horního menu. Spodní část obrazovky je vyčleněna pro stavový panel.

<div align="center" margin="0" padding="0">
<img src="https://raw.githubusercontent.com/parezj/EMBO/master/screenshots/scope.png" alt="EMBO scope" width="800">
</div>

Popis ovládacích panelů: 
- **Hlavní panel** — leží vpravo nahoře, základní režimy (Run, Stop, Single)
- **Trigger** — nastavení spouštění
- **Horizontal** — nastavení časové základny, resp. vzorkovací frekvence a paměti
- **Vertical** — nastavení kanálů a jejich zisk a posun
- **Utils** — doplňkové funkce (průměrování, rozlišení, FFT)
- **Cursors** — ovládání kurzorů
- **Measure** — indikátory měřených parametrů

#### Hlavní panel 
Podobně jako u většiny osciloskopů i EMBO disponuje 3 hlavními režimy: Run, Stop a Single. Implementace těchto režimů je inspirována stolními digitálními osciloskopy (Agilent, Tektronix). Režim Run je primární režim s kontinuální akvizicí dat. Režimu Stop slouží k zastavení akvizice a k analýze signálu. Speciální režim Single slouží pro zachycení jednorázového děje. Dále v tomto panelu má uživatel možnost resetovat zoom nebo celý přístroj.

#### Trigger
Nastavení spuštění je také inspirováno stolními přístroji. Výchozí je vždy režim Auto, který kombinuje funkcionalitu režimu Normal s časovým limitem, který umožňuje vidět signál ve všech případech. Dále je nastavitelná hrana spouštění (Slope), kanál (Channel), spouštěcí úroveň (Level) a pre-trigger. V režimu Normal a Single má uživatel možnost vynutit trigger, což slouží jako rychlý náhled. Indikační LED jménem Trig´d svítí zeleně, pokud byl trigger úspěšný (bliká s každou novou zprávou).

#### Horizontal
Nastavovat horizontální parametry lze ve 2 režimech. V manuálním režimu uživatel nastavuje vzorkovací frekvenci (Fs) a hloubku paměti na kanál (Mem). V automatickém režimu jsou tyto 2 parametry optimalizovány na základě celkové délky zobrazovaného signálu (Width). Tento přístup byl zvolen proto, že klasická mřížka a nastavení (sekunda/dílek) zde nedává smysl, protože graf je interaktivní a uživatel s ním může libovolně zoomovat a hýbat. Dále jsou zobrazeny 2 důležité informace:  Reálná vzorkovací frekvence (Real Fs) s přesností na 6 řádů je potřebná při vzorkování v ekvivalentním čase a následnému přepočtu frekvence. Maximální přípustná impedance zdrojového signálu, kterou je nutné nepřekročit pro korektní měření.

#### Vertical 
Vertikální nastavení umožňuje zapínat jednotlivé kanály, nastavovat jejich zisk a posun.

#### Utils, Cursors a Measure 
Průměrování (Average) je vhodné pro vyhlazení zarušeného signálu. Případný 8-bitový režim urychlí přenos dat na úkor snížení rozlišení a FFT zapíná režim spektrální analýzy. Kurzory (Cursors) slouží pro měření signálu v obou osách a měřené parametry (Measure) představují základní informaci o signálu.

Popis horního menu:
- **Export** — export dat ve formátu CSV, TXT nebo jako screenshot
- **Plot** — nastavení zobrazení grafu a interpolace
- **Measure** — nastavení měřených parametrů
- **FFT** — natavení FFT spektrální analýzy
- **Math** — ovládání speciálních režimů (rozdíl, XY)

### Logický analyzátor
Logický analyzátor zprostředkovává doplňkovou funkcionalitu osciloskopu pro sledování rychlých digitálních signálů. Podobně jako osciloskop je přístroj rozdělen do dvou hlavních bloků. V levém bloku je interaktivní graf, který dynamicky zobrazuje příslušný počet kanálů, na rozdíl od osciloskopu ale pod sebou. V pravém bloků jsou hlavní ovládací prvky vycházející z osciloskopu. Doplňkové funkce se opět ovládají z horního menu. Spodní část obrazovky je vyčleněna pro stavový panel.

<div align="center" margin="0" padding="0">
<img src="https://raw.githubusercontent.com/parezj/EMBO/master/screenshots/la.png" alt="EMBO la" width="800">
</div>

Většina ovládacích prvků sdílí stejnou funkčnost i design s osciloskopem. Rozdíl je u triggeru, kde chybí spouštěcí úroveň, naopak přibyla možnost triggerovat na obě hrany (Both). Dále chybí vertikální zesílení a offset, protože pro logický analyzátor nemají smysl. Podobně také chybí režim průměrování, bitové rozlišení a FFT.

Popis ovládacích panelů: 
- **Hlavní panel** — leží vpravo nahoře, základní režimy (Run, Stop, Single)
- **Trigger** — nastavení spouštění
- **Horizontal** — nastavení časové základny, resp. vzorkovací frekvence a paměti
- **Vertical** — výběr zobrazených kanálů
- **Utils** — ovládání kurzorů, analýza dat (bude doplněna později)

### Voltmetr 
Voltmetr je poslední primární přístroj osciloskopu EMBO. Jeho okno je opět rozděleno na dva hlavní bloky. V levém bloku je interaktivní graf, pod kterým jsou zobrazeny měřené parametry a ovladač kurzorů. V pravém bloku jsou pod sebou 4 panely kanálů a pod nimi je hlavní ovládací panel (Settings).

<div align="center" margin="0" padding="0">
<img src="https://raw.githubusercontent.com/parezj/EMBO/master/screenshots/vm.png" alt="EMBO vm" width="800">
</div>

Popis nastavitelných parametrů:
- **Scale** — konstanta, kterou je na násobeno napětí kanálu 
- **Average** — počet průměrovaných hodnot (1 znamená vypnuto)
- **Plot Points** — počet zobrazených bodů v grafu

Vzorkovací frekvence je fixně nastavena na 100 Sps. Je to dvojnásobek frekvence napětí z veřejné sítě. Pokud je vypnut režim průměrování, hodnota NPLC (Number of Power Line Cycles) se rovná 0.5. Pokud budeme tuto hodnotu zvyšovat (zvyšováním hodnoty Average), výrazně potlačíme indukovaný 50 Hz šum. Čím vyšší hodnota Average, resp. NPLC, tím pomaleji voltmetr měří a tím více je potlačen šum. Režim Average tedy zvyšuje přesnost při měření konstantního signálu.

Kromě hlavního nastavení lze využít doplňkové možnosti z horního menu, které je podobné jako u osciloskopu. Vedle standardního nastavení, jako je interpolace nebo nastavení měřených parametrů, lze např. zapnout kontinuální nahrávání do souboru (CSV nebo TXT). Zaznamenaný signál bude mít vzorkovací frekvenci 100 Sps.

### Čítač 
Čítač je jednoduchý sekundární přístroj, který lze paralelně provozovat s ostatními přístroji. Lze nastavit režim Slow (pro signály do cca 1 MHz) a režim Fast (pro signály cca od 1 MHz). Pro pomalé signály trvá měření delší dobu. V případě že nebyl detekován signál během 2 sekund nastane timeout. Při použití s osciloskopem nebo logickým analyzátorem při maximální vzorkovací frekvenci může docházet k přetížení DMA a vypadávání vzorků.

<div align="center" margin="0" padding="0">
<img src="https://raw.githubusercontent.com/parezj/EMBO/master/screenshots/cntr.png" alt="EMBO cntr" width="250">
</div>

### PWM generátor 
Generátor PWM signálu existuje buď s 1 nebo 2 kanály. V případě 2 kanálů jde o synchronní generátor, který může být použit pro ovládání motorů nebo pro simulaci signálů z kvadraturního enkodéru. Frekvence se nastavuje shodná pro oba kanály. Dále lze nastavit střídu zvlášť pro kanál a offset druhého kanálu. Opět je třeba zdůraznit, že při vysokých hodnotách
vzorkovací frekvence osciloskopu může docházet k nežádoucímu ovlivnění měřeného signálu.

<div align="center" margin="0" padding="0">
<img src="https://raw.githubusercontent.com/parezj/EMBO/master/screenshots/pwm.png" alt="EMBO pwm" width="300">
</div>

### Signálový generátor 
Signálový generátor je sekundární volitelný přístroj, který využívá 12-bitové DAC. Je dostupný pouze u těch mikrořadičů, které disponují DAC, jako je např. F303RE. Uživatel může nastavit frekvenci, amplitudu a ofset. U vysokých frekvencích je dynamicky snížena velikost výstupního bufferu, tedy vzorků na periodu (Size), aby DAC stíhal generovat. Dále je zobrazena reálná frekvence generovaného signálu a velikost amplitudy v milivoltech. V režimu Constant se chová generátor jako zdroj napětí.

<div align="center" margin="0" padding="0">
<img src="https://raw.githubusercontent.com/parezj/EMBO/master/screenshots/sgen.png" alt="EMBO sgen" width="450">
</div>

## 5. Třídní diagram PC aplikace

<div align="center" margin="0" padding="0">
<img src="https://raw.githubusercontent.com/parezj/EMBO/master/img/qt_classes_png_en.png" alt="EMBO PC class diagram" width="700">
</div>

## 6. Blokové schéma firmware

<div align="center" margin="0" padding="0">
<img src="https://raw.githubusercontent.com/parezj/EMBO/master/img/periferie_png_en.png" alt="EMBO fw block diagram" width="700">
</div>

## 7. Použité IP
- **[SCPI Parser](https://github.com/j123b567/scpi-parser)**  (Jan Breuer)
- **[FreeRTOS](https://www.freertos.org/)**
- **[SEGGER SystemView](https://www.segger.com/products/development-tools/systemview/)**
- **[QCustomPlot](https://www.qcustomplot.com/)**
- **[FFTW3](http://www.fftw.org/)**
- **[qBreakpad](https://github.com/buzzySmile/qBreakpad)**
- **[Google Breakpad](https://github.com/google/breakpad)**
- **[QSimpleUpdater](https://github.com/alex-spataru/QSimpleUpdater)**
