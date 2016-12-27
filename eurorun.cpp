#include<iostream>
#include<vector>
#include <fstream>
#include <iterator>
#include <string>
#include <algorithm>
#include <sstream>

#include "csv.h"


// GlobalVariabl
typedef struct{
	int  prize[2];
	uint8_t rankings[10];
	float prob;
}key_with_rank;

typedef struct{
	int draw_number=0;
    int histogram[256];
    int histogram2[256];
    int histogram_max_time_without_win[256];
    int number_histogram[60];
    int star_histogram[20];
    int history_max[2000];
	float history_prob_max[2000];
	float history_prob_min[2000];
	float history_prob_sai[2000];
	int  prize[2];
	bool files_ok;
	char rankings[10];
	float prob;
}general_info;


//=======================================================================================
//
//======================================================================================
void report_html(int draw_number, std::string message){
	 std::ofstream my_state_file;
    my_state_file.open ("report_file.html");
     my_state_file << "Hello, I am in "<<draw_number <<" and my message is"<< message <<" ";
    //my_state_file << "I am in the draw number = " << draw_number ;
    my_state_file.close();
	
}

void report_html_graph(std::string name_f, int *values, int max){
	 std::ofstream my_state_file;
	 //orme about at https://developers.google.com/chart/interactive/docs/gallery/columnchart
    my_state_file.open (name_f.c_str() ); //"report_file_h1.html");
     my_state_file << "<html> \n <head> \n <script type=\"text/javascript\" src=\"https://www.gstatic.com/charts/loader.js\"> \n </script> \n <script type=\"text/javascript\"> \n google.charts.load('current', {'packages':['bar']});; \n google.charts.setOnLoadCallback(drawChart);\n function drawChart() {\n var data =new google.visualization.DataTable();\n data.addColumn('number', 'Number'); \n  data.addColumn('number', 'Number of outs');\n data.addRows([\n  ";
    
    for(int jj=0;jj<max;jj++){
		 my_state_file << "["<< jj <<", "<< (int)values[jj] <<" ]," << std::endl;
    	
    }
    my_state_file << "["<< max <<", "<< 0  <<" ] " << std::endl;
    my_state_file << " ]); \n" << "var options = {'title':'How Much took the winner take a prize',  'width':800, 'height':300}; \n var chart = new google.charts.Bar(document.getElementById('chart_div')); \n chart.draw(data, options); }   \n </script>\n  </head\n> <body> \n  <div id=\"chart_div\" style=\"width: 900px; height: 500px;\">\n</div>\n </body>\n</html>";
    my_state_file.close();
	
}


void report_html_graphf(std::string name_f, float *values, int max){
	 std::ofstream my_state_file;
	 //orme about at https://developers.google.com/chart/interactive/docs/gallery/columnchart
    my_state_file.open (name_f.c_str() ); //"report_file_h1.html");
     my_state_file << "<html> \n <head> \n <script type=\"text/javascript\" src=\"https://www.gstatic.com/charts/loader.js\"> \n </script> \n <script type=\"text/javascript\"> \n google.charts.load('current', {'packages':['bar']});; \n google.charts.setOnLoadCallback(drawChart);\n function drawChart() {\n var data =new google.visualization.DataTable();\n data.addColumn('number', 'Number'); \n  data.addColumn('number', 'Number of outs');\n data.addRows([\n  ";
    
    for(int jj=0;jj<max;jj++){
		 my_state_file << "["<< jj <<", "<< (float)values[jj] <<" ]," << std::endl;
    	
    }
    my_state_file << "["<< max <<", "<< 0  <<" ] " << std::endl;
    my_state_file << " ]); \n" << "var options = {'title':'How Much took the winner take a prize',  'width':800, 'height':300}; \n var chart = new google.charts.Bar(document.getElementById('chart_div')); \n chart.draw(data, options); }   \n </script>\n  </head\n> <body> \n  <div id=\"chart_div\" style=\"width: 900px; height: 500px;\">\n</div>\n </body>\n</html>";
    my_state_file.close();
	
}


int main(int argc, char *argv[]){
 
  general_info H;
  H.draw_number=0;

  
  

  
  //=========================================================================================
  // The DRAW get info
  //=========================================================================================
  io::CSVReader<9> in("test2.csv");
  in.read_header(io::ignore_extra_column,"data","c1","c2","c3","c4","c5","s","e1","e2");
  std::string key_date; 
  int key[9];
  int buf_prize[10];
  

  std::string fileF;
  fileF.assign("data/data_GENERAL");
  fileF.append(".dat");
  std::ifstream file_input_temp3(fileF.c_str());
  bool reinit_data=true;
    	   	
  if(file_input_temp3.good()){
  	std::ifstream ise(fileF.c_str(), std::ios::binary);
                
    ise.seekg(0,std::ifstream::end);
    std::streampos fileSize2 = ise.tellg();
    //Global_vector_key.resize(fileSize2/sizeof(general_info));
    ise.seekg(0, std::ios_base::beg);
    ise.read((char*)&H,fileSize2);
    
    if(H.files_ok){
    	reinit_data=false;
    }else{
    	std::cout << "ERROR, please remove old data, this is demaged" << std::endl;
    	exit(0);
    }
  }
  
  if(reinit_data){
  	  for(int jj=0;jj<256;jj++){
    	H.histogram[jj]=0;
    	H.histogram2[jj]=0;
      }	
      for(int jj=0;jj<60;jj++){
      	H.number_histogram[jj]=0;
      }
      for(int jj=0;jj<20;jj++){
      	H.star_histogram[jj]=0;
      }
      
      for(int jj=0;jj<20;jj++){
        H.history_max[jj]=0;
	    H.history_prob_max[jj]=0;
	    H.history_prob_min[jj]=0;
	    H.history_prob_sai[jj]=0;
      }

  }
  
  
  int number_key=0;
  while(in.read_row(key_date, key[0], key[1], key[2], key[3],key[4],key[5],key[6],key[7])){
      std::cout << "|" << key[0] <<"  - " << key[1] << "  - " << key[2] <<"  - " << key[3] <<"  - " << key[4] <<" * " << key[6]<<" +  " << key[7] << std::endl;
    // do stuff with the data
    float prob_max=0.0;
    long long int prob_max_count=0;
    long long int prob_min_count=0;
    float win_prob_key;
    number_key++;
    int  number_without_win=0;
    
    std::ifstream infile("status.txt");
    std::string line;
    std::getline(infile, line);
    std::istringstream iss(line);
    if(line.compare(0,3,"run")==0){
       // std::cout << "ruuuu </br>" << std::endl;
       
    }else{
        std::cout << "Exit by PHP order</br>" << std::endl;
        exit(0);
    }
    infile.close();
    
   if( (number_key-1) != H.draw_number){
   		std::cout << "already readed this key." <<H.draw_number  << "()" <<number_key << "</br>" << std::endl;
    	
   }else{
	    
	   H.draw_number++;
	   H.number_histogram[key[0]]++;
	   H.number_histogram[key[1]]++;
	   H.number_histogram[key[2]]++;
	   H.number_histogram[key[3]]++;
       H.number_histogram[key[4]]++;
	   H.star_histogram[key[6]]++;
	   H.star_histogram[key[7]]++;
	    
	    
	   H.files_ok= false;
	   std::ofstream os (fileF.c_str(), std::ios::binary);
	   os.write((const char*)&H, 1 * sizeof(general_info));
	   os.close();
	    
	   report_html(H.draw_number,"I am reading the key...");
	  
	       long long int count_prizes=0;
	       long long int good_key=0;
	    //=========================================================================================
	    // The table history update
	    //=========================================================================================
	       for(int e1=1;e1<12;e1++){
	    	   	
	    	   	//======================================
	    	   	std::vector<key_with_rank>  Global_vector_key;
	    	   	long long int count=0;
	    	   	
	    	   	std::ostringstream file_number_set_of_data;  //temp as in temporary
	    		file_number_set_of_data<<e1;
	    		std::string file;
	    	    file.assign("data/data_");
	    	    file.append(file_number_set_of_data.str().c_str());
	    	    file.append(".dat");
	    	   	
	    	   	bool update_mode=false;
	    	   	//======================================
	    	   	
	    	   	std::ifstream file_input_temp(file.c_str());
	    	   	
	    	   	if(file_input_temp.good()){
	    	   		 update_mode=true;
	    	   		 std::ifstream is(file.c_str(), std::ios::binary);
	                
	                 is.seekg(0,std::ifstream::end);
	    			 std::streampos fileSize = is.tellg();
	                 Global_vector_key.resize(fileSize/sizeof(key_with_rank));
	                 is.seekg(0, std::ios_base::beg);
	    			 //long long int size2 = fileSize;
	    		     //is.seekg(0,std::ifstream::beg);
	    			 //Global_vector_key.resize(size2);
	    			 is.read((char*)&Global_vector_key[0],fileSize);
	    			 //std::cout << "I am in" << count << "read" <<  fileSize/sizeof(key_with_rank) << "file size "<<fileSize << "</br>" << std::endl;
	    			 std::cout << "*" << std::endl;
	    	   	}else{
	    	   		std::cout << "*" << std::endl;
	    	   	}
	    	   	int key_run[5];
	    	  	for(int e2=e1+1;e2<13;e2++){
	    	     for(key_run[0]=1;key_run[0]<47;key_run[0]++){
	    	      for(key_run[1]=key_run[0]+1;key_run[1]<48;key_run[1]++){
	    	       for(key_run[2]=key_run[1]+1;key_run[2]<49;key_run[2]++){
	    	   	    for(key_run[3]=key_run[2]+1;key_run[3]<50;key_run[3]++){
	    	   	   	 for(key_run[4]=key_run[3]+1;key_run[4]<51;key_run[4]++){
	    		   	   count++;
	    		       if(update_mode==false) Global_vector_key.resize(count);
	    		       
	    		       if(Global_vector_key[count-1].rankings[3]>6) good_key++;
	    		       
	    		       int n_shots=0;
	    		       for(int ii=0;ii<5;ii++){
	    		       for(int jj=0;jj<5;jj++){
	    		        if(key[ii]==key_run[jj]) n_shots++;
	    		       }
	    		       }
	    		       
	    		       int e_shots=0;
	    		       if(e1==key[6]) e_shots++;
	    		       if(e1==key[7]) e_shots++;
	    		       if(e2==key[6]) e_shots++;
	    		       if(e2==key[7]) e_shots++;
	    		       
	    		       bool prize=false;
	    		       if(n_shots>1) prize=true;
	    		       if( (n_shots==1) && (e_shots==2)) prize=true;
	    		       
	    		       //==============================================================
	    		       //==============================================================
	    		       
	    		       if(prize)Global_vector_key[count-1].prize[0]++;
	    		       if(Global_vector_key[count-1].prize[0]>0) count_prizes++;
	    		       
	
	    		           		       //==============================================================
	    		       //==============================================================
	    		       for(int ii=0;ii<4;ii++){
	    		       	if(H.draw_number==1){
	    		       		Global_vector_key[count-1].rankings[ii] = 254;
	    		       		Global_vector_key[count-1].rankings[ii+4] = 254;
	    	      	     }else{
		    		       		Global_vector_key[count-1].rankings[ii]++;
		    		       		if(	Global_vector_key[count-1].rankings[ii] >254)
		    		       		  Global_vector_key[count-1].rankings[ii]=254;
		    		       		  
		    		       		Global_vector_key[count-1].rankings[ii+4]++;
		    		       		if(	Global_vector_key[count-1].rankings[ii+4] >254)
		    		       		  Global_vector_key[count-1].rankings[ii+4]=254;
	    		       	}
	    		       }
	    		       if(prize ){
	    		       	 for(int ii=0;ii<3;ii++){
	    		       	 	Global_vector_key[count-1].rankings[ii]=Global_vector_key[count-1].rankings[ii+1];
	    		       	 }
	    		       	 Global_vector_key[count-1].rankings[3]=0;
	    		       }
	    		       
	    		       if(n_shots>2 ){
	    		       	 for(int ii=0;ii<3;ii++){
	    		       	 	Global_vector_key[count-1].rankings[ii+4]=Global_vector_key[count-1].rankings[ii+4+1];
	    		       	 }
	    		       	 Global_vector_key[count-1].rankings[3+4]=0;
	    		       }
	   
	    		       if( (n_shots==5) && (e_shots==2)){
	    		       	   buf_prize[0]=(unsigned int)Global_vector_key[count-1].rankings[0];
	    		       	   buf_prize[1]=(unsigned int)Global_vector_key[count-1].rankings[1];
	    		       	   buf_prize[2]=(unsigned int)Global_vector_key[count-1].rankings[2];
	    		       	   buf_prize[3]=(unsigned int)Global_vector_key[count-1].rankings[3];
	    		       	   
	    		       	   buf_prize[4]=(unsigned int)Global_vector_key[count-1].rankings[4];
	    		       	   buf_prize[5]=(unsigned int)Global_vector_key[count-1].rankings[5];
	    		       	   buf_prize[6]=(unsigned int)Global_vector_key[count-1].rankings[6];
	    		       	   buf_prize[7]=(unsigned int)Global_vector_key[count-1].rankings[7];
	    		       	//   histogram[buf_prize[0]]++;
	    		       	   H.histogram[(unsigned int)buf_prize[2]]++; 
	    		       	   H.histogram2[(unsigned int)buf_prize[6]]++;
	    		       	   win_prob_key=Global_vector_key[count-1].prob;
	     		       	 //  histogram[buf_prize[2]]++;
	     		       	  // histogram[buf_prize[3]]++;    		       	   
	    		       }
	    		       
	    		       Global_vector_key[count-1].prob= ( (float)H.histogram[(unsigned int)Global_vector_key[count-1].rankings[3]]/(float)H.draw_number )* ((float)H.histogram2[(unsigned int)Global_vector_key[count-1].rankings[7]]/(float)H.draw_number);
	    		       
	    		       if(prob_max<Global_vector_key[count-1].prob){
	                        prob_max_count=0;
	                        prob_max=Global_vector_key[count-1].prob;
	    		       }else if(prob_max==Global_vector_key[count-1].prob){
	    		           prob_max_count++;
	    		       }
	    		       
	    		       if(Global_vector_key[count-1].prob==0){
	    		           prob_min_count++;
	    		       }
	    		       
	    		      if( number_without_win < Global_vector_key[count-1].rankings[3] ){
	    		      	number_without_win = Global_vector_key[count-1].rankings[3];
	    		      }

	    	    }}}}}}
	    	    // std::cout << "I am in" << count << "</br>" << std::endl;
	    	    std::ofstream os (file.c_str(), std::ios::binary);
	            long long int size1 = Global_vector_key.size();
	            //os.write((const char*)&Global_vector_key[0], sizeof(Global_vector_key));
	            os.write((const char*)&Global_vector_key[0], size1 * sizeof(key_with_rank));
	            os.close();
	       } //for
	       
	        std::cout << "in " << H.draw_number << "has prizes="<< count_prizes << "The last= !" << buf_prize[0] << "!" << buf_prize[1] << "!" << buf_prize[2] << "!" << buf_prize[3] << "The last (2equal)= !" << buf_prize[4] << "!" << buf_prize[5] << "!" << buf_prize[6] << "!" << buf_prize[7] <<  "--- Good key= "<< good_key << "prob=" << prob_max << " ii= "<< prob_max_count << "this won itwh" <<  win_prob_key<< "prob min="<< prob_min_count <<"</br>" <<  std::endl;
	        report_html_graph("report_file_h1.html",H.histogram, 255);
	        report_html_graph("report_file_h2.html",H.histogram2, 255);
	        report_html_graph("report_file_h3.html", H.number_histogram, 51);
	        report_html_graph("report_file_h4.html",H.star_histogram, 14);
	        
	        H.histogram_max_time_without_win[number_without_win]++;
	        report_html_graph("report_file_h5.html",H.histogram_max_time_without_win, 255);
	        
	        H.history_max[H.draw_number]=number_without_win;
	        report_html_graph("report_file_h6.html",H.history_max, H.draw_number+1);
	        
	        H.history_prob_max[H.draw_number]=prob_max;
	        report_html_graphf("report_file_h7.html",H.history_prob_max, H.draw_number+1);
          //	float history_prob_min[2000];
	        H.history_prob_sai[H.draw_number]= win_prob_key;
	        report_html_graphf("report_file_h8.html",H.history_prob_sai, H.draw_number+1);

	        
	        H.files_ok=true;
	        std::ofstream ose(fileF.c_str(), std::ios::binary);
	        ose.write((const char*)&H, 1 * sizeof(general_info));
	        ose.close();
   }
  } //while
	
//}}
  
   


   return 0;
}