#include<iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream> 
#include <fstream>
#include <cmath>
#include <iomanip>
using namespace std;

#define SPLITOFCSV ','
#define NUMOFPARAMETERS 3
#define PERCENTAGE 100
#define PREFIX "classifier_"
#define SUFFIX ".csv"
#define DATASETFILENAME "dataset.csv"
#define LABELSFILENAME "labels.csv"
#define SLASH "/"

int countNumOfClassifiers(string file_location2){
	int counter =0 , i=0 ,condition=1 ;
	while(condition){
		ifstream classifier_i_read;
		string file_name = file_location2 + SLASH + PREFIX + to_string(i) + SUFFIX;
		classifier_i_read.open(file_name.c_str());
		if (classifier_i_read.is_open()){
			counter++;
			classifier_i_read.close();
			i++;
		}
		else condition=0 ;
	}
	return counter;
}

vector<string> splitAndMakeDataVector(string str, char delim, vector<string> out){
	size_t start;
	size_t end = 0;
	while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
	{
		end = str.find(delim, start);
		out.push_back(str.substr(start, end - start));
	}
	return out;
}

vector<vector<string> > dataFromGivenInputs(string file_location1){
	vector<vector<string> >data;
	ifstream data_read ;
	string file_name = file_location1+SLASH+DATASETFILENAME;
	data_read.open(file_name);
	int ignor_first_line = 1;
	string line = "";
	vector<string> splited_line;  
	while(getline(data_read,line)){
		if(ignor_first_line == 1) ignor_first_line = 0 ;
		else {
			splited_line = splitAndMakeDataVector(line, SPLITOFCSV,splited_line);
			data.push_back(splited_line);
			splited_line.clear();
		}
		line.erase();
	}
	data_read.close();
	return data;
}

int classCounter(string file_location2){
	int class_counter = 0; 
	ifstream classifier_i_read; 
	string file_name = file_location2 +SLASH + PREFIX + to_string(1) + SUFFIX;
	classifier_i_read.open(file_name.c_str());
	int ignor_first_line = 1;
	string line = "";
	vector<string> splited_line;  
	while(getline(classifier_i_read,line)){
		if(ignor_first_line == 1) ignor_first_line = 0;
		else {
			class_counter++;
		}
		line.erase();
	}	
	classifier_i_read.close();
	return class_counter;
}

vector<vector<double> > stringToDouble2D(vector<vector<string> > string_data){
	vector<vector<double> > double_data(string_data.size() , vector<double> (string_data[0].size() ,0));
	for(int i = 0 ; i < string_data.size() ; i++){
		for(int j = 0 ; j < string_data[i].size() ; j++){
			double_data[i][j] = stod(string_data[i][j]);
		}
	}
		return double_data;
}

vector<vector<vector<double> > > stringToDouble3D(vector<vector<vector<string> > > classifiers_content_string ,string file_location2){
	int all_classes = classCounter(file_location2);
	int num_of_classifiers = countNumOfClassifiers(file_location2);
	vector<vector<vector<double> > > classifiers_content( num_of_classifiers, vector<vector<double> >(all_classes, vector<double>(NUMOFPARAMETERS, 0)));
	for(int classifier_num =0; classifier_num < num_of_classifiers; classifier_num++ ){
		for(int class_num =0; class_num < all_classes ; class_num++){
			for(int parameter_num =0; parameter_num < NUMOFPARAMETERS ; parameter_num++){
				classifiers_content[classifier_num][class_num][parameter_num] = stod(classifiers_content_string[classifier_num][class_num][parameter_num]);
			}
		}
	}
	return classifiers_content;
}

vector<vector<double> > putDatasetIn2D(string file_location1){
	vector<vector<string> > string_data;
	vector<vector<double> > double_data;
	string_data = dataFromGivenInputs(file_location1); 
	return double_data = stringToDouble2D(string_data);
}

vector<int> putGivenLabelsInVec(string file_location1){
	vector<int> given_Labels;
	ifstream labels_read ;
	string file_name = file_location1+SLASH+LABELSFILENAME;
	labels_read.open(file_name);
	int ignor_first_line = 1;
	string line = "";
	while(getline(labels_read,line)){
		if(ignor_first_line == 1) ignor_first_line = 0;
		else {
			given_Labels.push_back(stoi(line));
		}
		line.erase();
	}
	labels_read.close();
	return given_Labels;
}

vector<vector<vector<string> > > putGivenClassifiersContentInVec(string file_location1, string file_location2){
	int class_counter = classCounter(file_location2) ;
	int num_of_classifiers = countNumOfClassifiers(file_location2);
	vector<vector<vector<string> > > classifiers_content;
	vector<vector<string> > each_class_content;
	for(int i=0 ; i<num_of_classifiers ; i++ ){
		ifstream classifier_i_read;
		string file_name =file_location2 +SLASH+ PREFIX + to_string(i) + SUFFIX;
		classifier_i_read.open(file_name.c_str());
		int ignor_first_line = 1;
		string line = "";
		vector<string> splited_line;  
		while(getline(classifier_i_read,line)){
			if(ignor_first_line == 1) ignor_first_line = 0 ;
			else {
				splited_line = splitAndMakeDataVector(line, SPLITOFCSV,splited_line);
				each_class_content.push_back(splited_line);
				splited_line.clear();
			}
		line.erase();
		}
		classifiers_content.push_back(each_class_content);
		each_class_content.clear();
		classifier_i_read.close();
	}
	return classifiers_content; 
}

int indexMaxOfLikelyInEveryClassifier(vector<double> class_for_every_classifier_content){
	int index_of_max = 0;
	for (int i=1; i<class_for_every_classifier_content.size(); i++){
		if(class_for_every_classifier_content[i]>class_for_every_classifier_content[index_of_max]) {
			index_of_max = i ;
		}
	}
	return index_of_max;
}

int giveMaxValueOfVec(vector<int> times_repeted_class){
	int max_value;
	int current_max = times_repeted_class[0];
	for (int i=1; i<times_repeted_class.size(); i++){
		if(times_repeted_class[i] > current_max) {
			current_max = times_repeted_class[i];
		}
	}
	max_value = current_max; 
	return max_value;
}

int chooseCorrectLabel(vector<int> temp_for_each_classifier_content ,string file_location2){
	int correct_label;
	int all_classes = classCounter(file_location2);
	vector<int> times_repeted_class;
	int current_class = 0;
	int count_repeated=0;
	while(current_class < all_classes){
		for(int i =0; i<temp_for_each_classifier_content.size() ;i++ ){
			if(current_class == temp_for_each_classifier_content[i]) count_repeated = count_repeated+1;
		}
		times_repeted_class.push_back(count_repeated);
		count_repeated = 0;
		current_class = current_class +1;
	}
	int max_element = giveMaxValueOfVec(times_repeted_class);
	int first_class_with_max_value;
	for(int j = 0 ; j < times_repeted_class.size() ; j++){
		if(times_repeted_class[j] == max_element){
			first_class_with_max_value = j ;
			break;
		}
	}
	return first_class_with_max_value;
}

vector<int> giveLabelsBasedOnClassifiers(vector<vector<double> > dataset, vector<vector<vector<double> > > classifiers_content, int num_of_all_datas, string file_location1, string file_location2){
	vector<int> labels_based_on_classifiers;
	vector<int> temp_for_each_classifier_content;
	vector<double> class_for_every_classifier_content;
	int all_classes = classCounter(file_location2);
	int num_of_classifiers = countNumOfClassifiers(file_location2);
	int num =0 ; 
	for(int i=0; i<num_of_all_datas; i++){
		for(int classifier_num =0; classifier_num < num_of_classifiers; classifier_num++ ){
			for(int class_num =0; class_num < all_classes ; class_num++){
				double likely = classifiers_content[classifier_num][class_num][0]*dataset[i][0]+classifiers_content[classifier_num][class_num][1]*dataset[i][1]+classifiers_content[classifier_num][class_num][2];
				class_for_every_classifier_content.push_back(likely);
			}
			temp_for_each_classifier_content.push_back(indexMaxOfLikelyInEveryClassifier(class_for_every_classifier_content));
			class_for_every_classifier_content.clear();
		}
		labels_based_on_classifiers.push_back(chooseCorrectLabel(temp_for_each_classifier_content , file_location2));
		temp_for_each_classifier_content.clear();
	}
	return labels_based_on_classifiers;
}

int main(int argc, char *argv[]) {
	vector<vector<double> > dataset;
	vector<int> given_labels;
	vector<vector<vector<string> > > classifiers_content_string;
	vector<vector<vector<double> > > classifiers_content;
	vector<int> labels_based_on_classifiers;
	string str_loc1(argv[1]);
	dataset = putDatasetIn2D(str_loc1);
	given_labels = putGivenLabelsInVec(str_loc1);
	string str_loc2(argv[2]);
	classifiers_content_string = putGivenClassifiersContentInVec(str_loc1,str_loc2);

	classifiers_content = stringToDouble3D(classifiers_content_string, str_loc2);
	labels_based_on_classifiers = giveLabelsBasedOnClassifiers(dataset, classifiers_content, dataset.size(), str_loc1, str_loc2);
	int all_data = dataset.size();
	int similar =0;
	for(int i=0;i<all_data;i++){
		if(given_labels[i] == labels_based_on_classifiers[i]) {
			similar = similar+1;
		}
	}
	double result = ((double)similar/(double)all_data) * PERCENTAGE;
	cout << "Accuracy: ";
	cout << fixed << setprecision(2) << result << "%" <<endl;

	return 0 ;
}