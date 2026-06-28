#include <Arduino.h>
#include <phyphoxBle.h> 
#define volt    4   // ADC1_4
#define amp     3   // ADC1_3
#define Rs      10  // 10 ohm GND-3

void setup()
{
   pinMode(volt, INPUT);
   pinMode(amp, INPUT);
   
   PhyphoxBLE::start("FÜN-BTI-07");

   //Percobaan
   PhyphoxBleExperiment FUNPLTB;  

   FUNPLTB.setTitle("PLTB");                    // Judul percobaan
   FUNPLTB.setCategory("FÜN");                  // Kelompok percobaan
   FUNPLTB.setDescription("Daya PLTB");

   PhyphoxBleExperiment::View firstView;
   firstView.setLabel("FirstView"); 

   // Grafik 1 - V(t) Tegangan
   PhyphoxBleExperiment::Graph firstGraph;    
   firstGraph.setLabel("Tegangan V(t)");
   firstGraph.setUnitX("s");
   firstGraph.setUnitY("V");
   firstGraph.setLabelX("waktu");
   firstGraph.setLabelY("tegangan");
   firstGraph.setChannel(0,1);                  // waktu dan tegangan ADC4

   // Grafik 2 - P(t) Daya
   PhyphoxBleExperiment::Graph secondGraph; 
   secondGraph.setLabel("Daya P(t)");
   secondGraph.setUnitX("s");
   secondGraph.setUnitY("mW");
   secondGraph.setLabelX("waktu");
   secondGraph.setLabelY("daya");
   //secondGraph.setStyle("dots");
   secondGraph.setChannel(0,2);                 // waktu dan daya 

   firstView.addElement(firstGraph);        
   firstView.addElement(secondGraph);       
   FUNPLTB.addView(firstView);     
   PhyphoxBLE::addExperiment(FUNPLTB);     
}


void loop()
{
  float adcV = analogRead(volt)*3.3/4095.0;  
  float adcA = analogRead(amp)*3.3/4095.0; 
  float tegangan = adcV;                    // tegangan
  float arus = (adcV - adcA) / Rs;          // arus, mA     
  float daya = tegangan * arus;             // daya, mW
  PhyphoxBLE::write(tegangan, daya);        // ch0: waktu, ch1: tegangan, ch2: daya
  delay(50);                                // tunggu 50 ms
}
