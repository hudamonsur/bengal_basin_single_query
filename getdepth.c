/* finding depth program */

#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include "getdepth.h"

float * getmantlevalues(float depth_m, float mindepth);
float * getcrustvalues(float depth_m, float mindepth);
float * getbhubanvalues(float depth_m, float maxdepth);
float * getbokabilvalues(float depth_m, float maxdepth);
float * gettipamvalues(float depth_m, float maxdepth);
float * getdupitilavalues(float depth_m, float maxdepth);
// float * getbasinvalues(float depth_m, float maxdepth);
float * getsurfacedepth(File *fp, float dlat, float dlong, float diflong, float diflat);

float * getdepth(float north_m, float east_m, float depth_m)
{
	float result[3];
	// FILE *fp1=NULL;
	// FILE *fp2=NULL;
	// FILE *fp3=NULL;
	// FILE *fp4=NULL;
	// FILE *fp5=NULL;
	// FILE *fp6=NULL;
	float minlat= 19.9;
	float maxlat= 27;
	float minlong= 86.5;
	float maxlong= 93.4;
	float value_precambrian;
	float value_bhuban;
	float value_bokabil;
	float value_tipam;
	float value_dupitila;
	float dlat = (maxlat-minlat)/2000;
	float dlong = (maxlong-minlong)/2000;
	int linecount = 0;
	int ch = 0;

	/*long bytevalue;*/
	// converting east and north values to lattitude and longitude

	float inputlat = minlat + north_m/(111.01*1000);
	float inputlong = minlong + east_m/(111.01*1000);

	/*float north_m = 23.8;
	float east_m = 87.45;*/
	float diflat = inputlat-minlat;
	float diflong = inputlong-minlong;

	// if (!fp1)
	// {
	// 	printf("Unable to open file!");
	// 	return 0;
	// }

	if(inputlat>maxlat || inputlat<minlat || inputlong<minlong || inputlong>maxlong){
		printf("The co-ordinate is out of the region");
		return 0;
	}

	// choosing among list of boreholes
	FILE *fp6 = fopen("borehole_list.txt","r");
	if (!fp6)
	{
		printf("Unable to open file!");
		return 0;
	}
	else {
		while(!feof(fp6)) {
			ch = fgetc(fp6);
			if(ch=='\n') {
				linecount++;
			}

		}
	}
	printf("%d",linecount);


	FILE *fp1=fopen("depth_precambrian.bin","rb");
	FILE *fp2=fopen("depth_bhuban.bin","rb");
	FILE *fp3=fopen("depth_bokabil.bin","rb");
	FILE *fp4=fopen("depth_tipam.bin","rb");
	FILE *fp5=fopen("depth_dupitila.bin","rb");

	value_precambrian = getsurfacedepth(File *fp1, float dlat, float dlong, float diflong, float diflat);
	value_bhuban = getsurfacedepth(File *fp2, float dlat, float dlong, float diflong, float diflat);
	value_bokabil = getsurfacedepth(File *fp3, float dlat, float dlong, float diflong, float diflat);
	value_tipam = getsurfacedepth(File *fp4, float dlat, float dlong, float diflong, float diflat);
	value_dupitila = getsurfacedepth(File *fp5, float dlat, float dlong, float diflong, float diflat);

	// else {
	// 	/* bilinear interpolation*/
	// 	long intervalnumberlongitude = diflong/dlong;
	// 	long intervalnumberlatitude = diflat/dlat;

	// 	if (intervalnumberlatitude==0 && intervalnumberlongitude==0){
	// 		byteval1 = intervalnumberlongitude*4 + 4;
	// 		fseek(fp1, byteval1, SEEK_SET);
	// 		fread(&value, 4, 1, fp1);
	// 	}

	// 	else if (intervalnumberlatitude==0){
	// 		byteval1 = intervalnumberlongitude*4;
	// 		fseek(fp1, byteval1, SEEK_SET);
	// 		fread(&value, 4, 1, fp1);
	// 	}

	// 	else if(intervalnumberlongitude==0){
	// 		byteval1 = intervalnumberlatitude*8000 + 4;
	// 		fseek(fp1, byteval1, SEEK_SET);
	// 		fread(&value, 4, 1, fp1);
	// 	}

	// 	else if(intervalnumberlatitude==2000 || intervalnumberlongitude==2000){
	// 		byteval1 = intervalnumberlatitude*8000 + intervalnumberlongitude*4;
	// 		fseek(fp1, byteval1, SEEK_SET);
	// 		fread(&value, 4, 1, fp1);
	// 	}

	// 	else {
	// 		byteval1 = intervalnumberlatitude*8000 + intervalnumberlongitude*4;
	// 		byteval2 = byteval1 + 8000;
	// 		byteval3 = byteval2 - 4;
	// 		byteval4 = byteval1 - 4;
	// 		float lat1 = intervalnumberlatitude*dlat+minlat;
	// 		float lat2 = lat1 + dlat;
	// 		float long1 = intervalnumberlongitude*dlong+minlong;
	// 		float long2 = long1 - dlong;

	// 		/* seeking values */
	// 		fseek(fp1, byteval1, SEEK_SET);
	// 		fread(&val1, 4, 1, fp1);
	// 		fseek(fp1, byteval2, SEEK_SET);
	// 		fread(&val2, 4, 1, fp1);
	// 		fseek(fp1, byteval3, SEEK_SET);
	// 		fread(&val3, 4, 1, fp1);
	// 		fseek(fp1, byteval4, SEEK_SET);
	// 		fread(&val4, 4, 1, fp1);


	// 		float R1 = ((long2-east_m)/(long2-long1))*val1 + ((east_m-long1)/(long2-long1))*val2;
	// 		float R2 = ((long2-east_m)/(long2-long1))*val4 + ((east_m-long1)/(long2-long1))*val3;

	// 		value = ((lat2-north_m)/(lat2-lat1))*R1 + ((north_m-lat1)/(lat2-lat1))*R2;
	// 	}

	// }
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);
	fclose(fp5);


	/*fseek(fp, 11576002, SEEK_SET);
	fread(&value, 4, 1, fp);*/

	/*printf("%f",value);*/
	float * output;
	if (depth_m>(value_precambrian*-1)+20000){
		output = getmantlevalues(depth_m, value);
		result[0] = *(output+0);
		result[1] = *(output+1);
		result[2] = *(output+2);

	}
		else if (depth_m>(value_precambrian*-1) && depth_m<=(value_precambrian*-1)+20000){
		output = getcrustvalues(depth_m, value);
		result[0] = *(output+0);
		result[1] = *(output+1);
		result[2] = *(output+2);

		}
		else if (depth_m>(value_bhuban*-1) && depth_m<=(value_precambrian*-1)) {
		//result = getbasinvalues(depth_m, value);
		output = getbasinvalues(depth_m, value);
		result[0] = *(output+0);
		result[1] = *(output+1);
		result[2] = *(output+2);

		}
		else if (depth_m>(value_bokabil*-1) && depth_m<=(value_bhuban*-1)){
		output = getbasinvalues(depth_m, value);
		result[0] = *(output+0);
		result[1] = *(output+1);
		result[2] = *(output+2);
		}
		else if (depth_m>(value_tipam*-1) && depth_m<=(value_bokabil*-1)){
		output = getbasinvalues(depth_m, value);
		result[0] = *(output+0);
		result[1] = *(output+1);
		result[2] = *(output+2);
		}
		else if (depth_m>(value_dupitila*-1) && depth_m<=(value_tipam*-1)){
		output = getbasinvalues(depth_m, value);
		result[0] = *(output+0);
		result[1] = *(output+1);
		result[2] = *(output+2);
		}
	return result;
	fclose(output);
	//printf("%f",value);
	//free(fp);

}

float * getsurfacedepth(File *fp, float dlat, float dlong, float diflong, float diflat){

	float value;
	float val1;
	float val2;
	float val3;
	float val4;
	long byteval1;
	long byteval2;
	long byteval3;
	long byteval4;

	if (!fp)
	{
		printf("Unable to open file!");
		return 0;
	}

	else {
		/* bilinear interpolation*/
		long intervalnumberlongitude = diflong/dlong;
		long intervalnumberlatitude = diflat/dlat;

		if (intervalnumberlatitude==0 && intervalnumberlongitude==0){
			byteval1 = intervalnumberlongitude*4 + 4;
			fseek(fp, byteval1, SEEK_SET);
			fread(&value, 4, 1, fp);
		}

		else if (intervalnumberlatitude==0){
			byteval1 = intervalnumberlongitude*4;
			fseek(fp, byteval1, SEEK_SET);
			fread(&value, 4, 1, fp);
		}

		else if(intervalnumberlongitude==0){
			byteval1 = intervalnumberlatitude*8000 + 4;
			fseek(fp, byteval1, SEEK_SET);
			fread(&value, 4, 1, fp1;
		}

		else if(intervalnumberlatitude==2000 || intervalnumberlongitude==2000){
			byteval1 = intervalnumberlatitude*8000 + intervalnumberlongitude*4;
			fseek(fp, byteval1, SEEK_SET);
			fread(&value, 4, 1, fp);
		}

		else {
			byteval1 = intervalnumberlatitude*8000 + intervalnumberlongitude*4;
			byteval2 = byteval1 + 8000;
			byteval3 = byteval2 - 4;
			byteval4 = byteval1 - 4;
			float lat1 = intervalnumberlatitude*dlat+minlat;
			float lat2 = lat1 + dlat;
			float long1 = intervalnumberlongitude*dlong+minlong;
			float long2 = long1 - dlong;

			/* seeking values */
			fseek(fp, byteval1, SEEK_SET);
			fread(&val1, 4, 1, fp);
			fseek(fp, byteval2, SEEK_SET);
			fread(&val2, 4, 1, fp);
			fseek(fp, byteval3, SEEK_SET);
			fread(&val3, 4, 1, fp);
			fseek(fp, byteval4, SEEK_SET);
			fread(&val4, 4, 1, fp);


			float R1 = ((long2-east_m)/(long2-long1))*val1 + ((east_m-long1)/(long2-long1))*val2;
			float R2 = ((long2-east_m)/(long2-long1))*val4 + ((east_m-long1)/(long2-long1))*val3;

			value = ((lat2-north_m)/(lat2-lat1))*R1 + ((north_m-lat1)/(lat2-lat1))*R2;
		}

	}
	return value;
}

float * getbhubanvalues(float depth_m, float maxdepth){

	float result[3];
	float minvs = 500;
	float maxvs = 2000;
	float mindensity = 2400;
	float maxdensity = 2800;
	float vs;
	float density;
	float vp;

	float mindepth = 0;
	if (maxdepth==0){
		vs = minvs;
		density = mindensity/1000;
	}
	else{
		maxdepth = maxdepth*-1;
		vs = (minvs+((maxvs-minvs)*(depth_m-mindepth))/(maxdepth-mindepth));
		vp = 2.2*vs;
		density = (mindensity+((maxdensity-mindensity)*(depth_m-mindepth))/(maxdepth-mindepth));
	}

	result[0]=vs;
	result[1]=vp;
	result[2]=density;

	return result;
}

float * getbokabilvalues(float depth_m, float maxdepth){

	float result[3];
	float minvs = 500;
	float maxvs = 2000;
	float mindensity = 2400;
	float maxdensity = 2800;
	float vs;
	float density;
	float vp;

	float mindepth = 0;
	if (maxdepth==0){
		vs = minvs;
		density = mindensity/1000;
	}
	else{
		maxdepth = maxdepth*-1;
		vs = (minvs+((maxvs-minvs)*(depth_m-mindepth))/(maxdepth-mindepth));
		vp = 2.2*vs;
		density = (mindensity+((maxdensity-mindensity)*(depth_m-mindepth))/(maxdepth-mindepth));
	}

	result[0]=vs;
	result[1]=vp;
	result[2]=density;

	return result;
}

float * gettipamvalues(float depth_m, float maxdepth){

	float result[3];
	float minvs = 500;
	float maxvs = 2000;
	float mindensity = 2400;
	float maxdensity = 2800;
	float vs;
	float density;
	float vp;

	float mindepth = 0;
	if (maxdepth==0){
		vs = minvs;
		density = mindensity/1000;
	}
	else{
		maxdepth = maxdepth*-1;
		vs = (minvs+((maxvs-minvs)*(depth_m-mindepth))/(maxdepth-mindepth));
		vp = 2.2*vs;
		density = (mindensity+((maxdensity-mindensity)*(depth_m-mindepth))/(maxdepth-mindepth));
	}

	result[0]=vs;
	result[1]=vp;
	result[2]=density;

	return result;
}

float * getdupitilavalues(float depth_m, float maxdepth){

	float result[3];
	float minvs = 500;
	float maxvs = 2000;
	float mindensity = 2400;
	float maxdensity = 2800;
	float vs;
	float density;
	float vp;

	float mindepth = 0;
	if (maxdepth==0){
		vs = minvs;
		density = mindensity/1000;
	}
	else{
		maxdepth = maxdepth*-1;
		vs = (minvs+((maxvs-minvs)*(depth_m-mindepth))/(maxdepth-mindepth));
		vp = 2.2*vs;
		density = (mindensity+((maxdensity-mindensity)*(depth_m-mindepth))/(maxdepth-mindepth));
	}

	result[0]=vs;
	result[1]=vp;
	result[2]=density;

	return result;
}

// float * getbasinvalues(float depth_m, float maxdepth){

// 	float result[3];
// 	float minvs = 500;
// 	float maxvs = 2000;
// 	float mindensity = 2400;
// 	float maxdensity = 2800;
// 	float vs;
// 	float density;
// 	float vp;

// 	float mindepth = 0;
// 	if (maxdepth==0){
// 		vs = minvs;
// 		density = mindensity/1000;
// 	}
// 	else{
// 		maxdepth = maxdepth*-1;
// 		vs = (minvs+((maxvs-minvs)*(depth_m-mindepth))/(maxdepth-mindepth));
// 		vp = 2.2*vs;
// 		density = (mindensity+((maxdensity-mindensity)*(depth_m-mindepth))/(maxdepth-mindepth));
// 	}

// 	result[0]=vs;
// 	result[1]=vp;
// 	result[2]=density;

// 	return result;
// }

float * getcrustvalues(float depth_m, float mindepth){

	float result[3];
	float minvs = 2700;
	float maxvs = 4200;
	float mindensity = 2700;
	float maxdensity = 3100;
	float vs;
	float density;
	float vp;

	mindepth = mindepth*-1;

	float maxdepth = mindepth+20000;
	vs = (minvs+((maxvs-minvs)*(depth_m-mindepth))/(maxdepth-mindepth));
	vp = 1.8*vs;
	density = (mindensity+((maxdensity-mindensity)*(depth_m-mindepth))/(maxdepth-mindepth));

	result[0]=vs;
	result[1]=vp;
	result[2]=density;

	return result;
}

float * getmantlevalues(float depth_m, float mindepth){

	float result[3];
	float minvs = 4500;
	float maxvs = 6000;
	float vs;
	float vp;
	float density;

	mindepth = mindepth*-1 + 20000;
	float maxdepth = 40000;
	vs = (minvs+((maxvs-minvs)*(depth_m-mindepth))/(maxdepth-mindepth));
	vp = 1.8*vs;
	density = 3300;

	result[0]=vs;
	result[1]=vp;
	result[2]=density;

	return result;
}




