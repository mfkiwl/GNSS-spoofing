#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int main()
{
    FILE *fp;
    char str[150];
    int ieph=0;
    int sv;
    // datetime_t t;
	// gpstime_t g;
	// gpstime_t g0;
    // int flags = 0x0;
	// double dt;

    if (NULL==(fp=fopen("gps_ephemeris.xml", "rt")))                    //change file name if saved differently
        printf("-1");

    // for (ieph=0; ieph<EPHEM_ARRAY_SIZE; ieph++)
	// 	for (sv=0; sv<MAX_SAT; sv++)
	// 		eph[ieph][sv].vflg = 0;


    //read emphimeris block

    // g0.week = -1;
	// ieph = 0;
    while(1)
    {
        if (NULL==fgets(str, 150, fp))
			break;
        int cnt=0;
        while(cnt<150 && str[cnt]!='<')
            cnt++;
        if(cnt<150 && str[cnt]=='<')
        {
            char tag[20]="";                                //variable  
            char innertag[150]="";                          //value
            int l,r,k;                                      //indices of '<' brackets
            l=cnt;
            while(cnt<150 && str[cnt]!='>')
            {
                cnt++;
            }
            r=cnt;
            while(cnt<150 && str[cnt]!='<')
                cnt++;
            k=cnt;
            if(cnt>=150)
                continue;
            strncpy(tag,str+l+1,r-l-1);
            strncpy(innertag,str+r+1,k-r-1);
            int prntvar=0;                              // print variable
            if(strcmp(tag,"PRN")==0)
            {
                printf("\n");
                prntvar=1;
                // sv = atoi(innertag)-1;
                //t.y=2013;
                //t.m=4;
                //t.d=4;
                //t.hh=8;
                //t.mm=0;
                //t.sec=0.0;


                // date2gps(&t, &g);
		
                // if (g0.week==-1)
                //     g0 = g;

                // Check current time of clock
                // dt = subGpsTime(g, g0);
                
                // if (dt>SECONDS_IN_HOUR)
                // {
                //     g0 = g;
                //     ieph++;                          // a new set of ephemerides

                //     if (ieph>=EPHEM_ARRAY_SIZE)
                //         break;
                // }

                // Date and time
                // eph[ieph][sv].t = t;

                // // SV CLK
                // eph[ieph][sv].toc = g;

            }
            else if(strcmp(tag,"M_0")==0)
            {
                prntvar=1;
                // eph[ieph][sv].m0 = atof(innertag);
            }
            else if(strcmp(tag,"delta_n")==0)
            {
                prntvar=1;
                // eph[ieph][sv].deltan = atof(innertag);
            }
            else if(strcmp(tag,"ecc")==0)
            {
                prntvar=1;
                // eph[ieph][sv].ecc = atof(innertag);
                // eph[ieph][sv].sq1e2 = sqrt(1.0 - eph[ieph][sv].ecc*eph[ieph][sv].ecc);
            }
            else if(strcmp(tag,"sqrtA")==0)
            {
                prntvar=1;
                // eph[ieph][sv].sqrta = atof(innertag);
                // eph[ieph][sv].A = eph[ieph][sv].sqrta * eph[ieph][sv].sqrta;
                // eph[ieph][sv].n = sqrt(GM_EARTH/(eph[ieph][sv].A*eph[ieph][sv].A*eph[ieph][sv].A)) + eph[ieph][sv].deltan;
            }
            else if(strcmp(tag,"OMEGA_0")==0)
            {
                prntvar=1;
                // eph[ieph][sv].omg0 = atof(innertag);  
            }
            else if(strcmp(tag,"i_0")==0)
            {
                prntvar=1;
                // eph[ieph][sv].inc0 = atof(innertag);                
            }
            else if(strcmp(tag,"omega")==0)
            {
                prntvar=1;
                // eph[ieph][sv].omgkdot = atof(innertag); 
            }
            else if(strcmp(tag,"OMEGAdot")==0)
            {
                prntvar=1;
                // eph[ieph][sv].omgdot = atof(innertag); 
            }
            else if(strcmp(tag,"idot")==0)
            {
                prntvar=1;
                // eph[ieph][sv].idot = atof(innertag);
            }
            else if(strcmp(tag,"Cuc")==0)
            {
                prntvar=1;
                // eph[ieph][sv].cuc = atof(innertag);
            }
            else if(strcmp(tag,"Cus")==0)
            {
                prntvar=1;
                // eph[ieph][sv].cus = atof(innertag);
            }
            else if(strcmp(tag,"Crc")==0)
            {
                prntvar=1;
                // eph[ieph][sv].crc = atof(innertag);
            }
            else if(strcmp(tag,"Crs")==0)
            {
                prntvar=1;
                // eph[ieph][sv].crs = atof(innertag);
            }
            else if(strcmp(tag,"Cic")==0)
            {
                prntvar=1;
                // eph[ieph][sv].cic = atof(innertag);
            }
            else if(strcmp(tag,"Cis")==0)
            {
                prntvar=1;
                // eph[ieph][sv].cis = atof(innertag);
            }
            else if(strcmp(tag,"af0")==0)
            {
                prntvar=1;
                // eph[ieph][sv].af0 = atof(innertag);
            }
            else if(strcmp(tag,"af1")==0)
            {
                prntvar=1;
                // eph[ieph][sv].af1 = atof(innertag);
            }
            else if(strcmp(tag,"af2")==0)
            {
                prntvar=1;
                // eph[ieph][sv].af2 = atof(innertag);
            }
            else if(strcmp(tag,"IODE_SF2")==0 || strcmp(tag,"IODE_SF3")==0)
            {
                prntvar=1;
                // eph[ieph][sv].iode = (int)atof(innertag);             
            }
            else if(strcmp(tag,"code_on_L2")==0)
            {
                prntvar=1;
                // eph[ieph][sv].codeL2 = (int)atof(innertag);
            }
            else if(strcmp(tag,"SV_health")==0)
            {
                prntvar=1;
                // eph[ieph][sv].svhlth = (int)atof(innertag);
                // if ((eph[ieph][sv].svhlth>0) && (eph[ieph][sv].svhlth<32))
			    //     eph[ieph][sv].svhlth += 32;
            }
            else if(strcmp(tag,"TGD")==0)
            {
                prntvar=1;
                // eph[ieph][sv].tgd = atof(innertag);
            }
            else if(strcmp(tag,"IODC")==0)
            {
                prntvar=1;
                // eph[ieph][sv].iodc = (int)atof(innertag);
            }
            else if(strcmp(tag,"toe")==0)
            {
                prntvar=1;
                // eph[ieph][sv]. = atof(innertag);             // doubt
            }
            else if(strcmp(tag,"toc")==0)
            {
                prntvar=1;
                // eph[ieph][sv]. = atof(innertag);             // doubt
            }
            else if(strcmp(tag,"tow")==0)
            {
                prntvar=1;
                // eph[ieph][sv]. = atof(innertag);             // doubt
            }
            else if(strcmp(tag,"WN")==0)
            {
                prntvar=1;
                // eph[ieph][sv]. = atof(innertag);             // extra info
            }
            else if(strcmp(tag,"satClkDrift")==0)
            {
                prntvar=1;
                // eph[ieph][sv]. = atof(innertag);             // extra info
            }
            else if(strcmp(tag,"dtr")==0)
            {
                prntvar=1;
                // eph[ieph][sv]. = atof(innertag);             // extra info
            }
            else if(strcmp(tag,"L2_P_data_flag")==0)
            {
                prntvar=1;
                // eph[ieph][sv]. = atof(innertag);             // extra info
            }
            else if(strcmp(tag,"SV_accuracy")==0)
            {
                prntvar=1;
                // eph[ieph][sv]. = atof(innertag);             // extra info
            }
            else if(strcmp(tag,"AODO")==0)
            {
                prntvar=1;
                // eph[ieph][sv]. = atof(innertag);                 // extra info
            }
            else if(strcmp(tag,"fit_interval_flag")==0)
            {
                prntvar=1;
                // eph[ieph][sv]. = atof(innertag);                 // extra info
            }
            else if(strcmp(tag,"spare1")==0)
            {
                prntvar=1;
                // eph[ieph][sv]. = atof(innertag);                 // extra info
            }
            else if(strcmp(tag,"spare2")==0)
            {
                prntvar=1;
                // eph[ieph][sv]. = atof(innertag);                 // extra info
            }
            else if(strcmp(tag,"integrity_status_flag")==0)
            {
                prntvar=1;
                // eph[ieph][sv]. = atof(innertag);                 // extra info
            }
            else if(strcmp(tag,"alert_flag")==0)
            {
                prntvar=1;
                // eph[ieph][sv]. = atof(innertag);                 // extra info
            }
            else if(strcmp(tag,"antispoofing_flag")==0)
            {
                prntvar=1;
                // eph[ieph][sv]. = atof(innertag);                 // extra info
            }
            if(prntvar==1)
            {
                printf("%s : %0.30f\n",tag,atof(innertag));
            }
        }
    }
    fclose(fp);
    // if (g0.week>=0)
	// 	ieph += 1;

    // return(ieph);

}