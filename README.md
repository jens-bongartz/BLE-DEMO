# BLE-DEMO
1. DEMOcentral.ino<br>
2. DEMOperipheral.ino<br>
<br>
DEMOperipheral (45 Zeilen lang) erzeugt einen DEMO-Service mit einer einzigen Characteristic, die "Counter" heißt. Dahinter verbirgt sich eine int-Variable die kontinuierlich hochgezählt wird und per BLE kommuniziert wird (writeValue).<br>
<br>
DEMOcentral (63 Zeilen lang) kann auf dem zweiten Nano 33 die Daten des Peripherals empfangen (readValue) und an den angeschlossen Computer weitersenden.<br>
