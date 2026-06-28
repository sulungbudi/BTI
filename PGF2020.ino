#include <phyphoxBle.h> 

void setup()
{
   pinMode(34, INPUT);
   pinMode(35, INPUT);
   
   PhyphoxBLE::start("PGF2020");

   //Percobaan
   PhyphoxBleExperiment PGF2020;  

   PGF2020.setTitle("Fisika Unpar");          // Judul percobaan
   PGF2020.setCategory("FUN");                // Kelompok percobaan
   PGF2020.setDescription("Grafik Pengukuran dari pin 34 dan pin 35 ESP32");

   PhyphoxBleExperiment::View firstView;
   firstView.setLabel("FirstView"); 

   // Grafik 1 - V(t) Tegangan pada pin 34
   PhyphoxBleExperiment::Graph firstGraph;    
   firstGraph.setLabel("Tegangan pada pin 34 - V(t)");
   firstGraph.setUnitX("s");
   firstGraph.setUnitY("V");
   firstGraph.setLabelX("waktu");
   firstGraph.setLabelY("tegangan");
   firstGraph.setChannel(0,1);                // waktu dan tegangan pin 34

   // Grafik 2 - I(V) Konstanta Planck
   PhyphoxBleExperiment::Graph secondGraph; 
   secondGraph.setLabel("Konstanta Planck - I(V)");
   secondGraph.setUnitX("V");
   secondGraph.setUnitY("mA");
   secondGraph.setLabelX("tegangan");
   secondGraph.setLabelY("arus");
   secondGraph.setStyle("dots");
   secondGraph.setChannel(1,2);               // tegangan pada pin 34 dan pin 35

   firstView.addElement(firstGraph);        
   firstView.addElement(secondGraph);       
   PGF2020.addView(firstView);     
   PhyphoxBLE::addExperiment(PGF2020);     
}


void loop()
{
  float adc34 = analogRead(34)*3.3/4095.0;  // tegangan pin 34
  float adc35 = analogRead(35)*3.3/4095.0;  // tegangan pin 35
  float tegangan = adc34 - adc35;           // untuk percobaan ini tegangan = tegangan pin 34 - tegangan pin 35
  float arus = adc35 * 10;                  // menggunakan resistor 100 ohm     
  PhyphoxBLE::write(tegangan, arus);        // ch1 tegangan, ch2 arus
  delay(50);                            // tunggu 50 ms
}
