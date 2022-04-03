#include <stdio.h> 
#include <conio.h> 
#include <stdlib.h>
#include <string.h>

struct takip{ 
    int 	hesapno; 
    char 	ad[10]; 
    char 	soyad[20]; 
    char 	telno[11];
    int 	bakiye;
};
    
    void dosyayarat(){
		FILE *d1;
   		d1 = fopen ("banka.dat", "wb"); 
   		if (d1 == NULL){
			printf("Veri dosyasi olusturulamadý! Programdan cikiliyor.");
			exit(1);
		}
      
    	takip bos_hesap = {-1, "", "", "", 0}; 
      	int i;
		for (i = 1; i < 100; ++i){
	    	fwrite (&bos_hesap, sizeof(struct takip), 1, d1);
	  	}     
    	fclose(d1);
	}

    void hesapac(){
    	FILE *d1;
        takip tkp;
        
        if ( (d1 = fopen("banka.dat", "r+b") ) == NULL ){
     		printf ("Dosya acilamadi...");
            //break;
            
     	}
 
        printf("Yeni Hesap Aciliyor");

        int hno;
        bool valid = false;
		do{
	        printf("\nHesap No : ");
	        scanf("%d", &hno);
	        if (hno <1 || hno >100){
	        	printf("\nHesap no 1-100 araliginda olmalidir!"); 
			} else {
		        fseek(d1, (hno-1) * sizeof(struct takip), SEEK_SET);
		        fread(&tkp, sizeof(struct takip), 1, d1);
		        
		        if (tkp.hesapno!=-1){
		        	printf("\n%d nolu hesap daha olusturulmus! Lutfen baska bir hesap no seciniz!", hno);
				} else {
					valid = true;
				}
			}
        }
        while (not valid);   
        tkp.hesapno = hno;
		     
        printf("\nAdi : ");
        scanf("%s", &tkp.ad);
        printf("\nSoyadi : ");
        scanf("%s", &tkp.soyad);
        
        valid = false;
		do{
	        printf("\nCep Telefonu (5XXXXXXXXX) : ");
	        scanf("%s", &tkp.telno);
	        if ((tkp.telno[0] == '0') || (strlen(tkp.telno) != 10)){
	        	printf("\nTelefon numarasi basinda '0' olmadan 10 hane olarak yazilmalidir!"); 
			} else {
				valid = true;
			}
        }
        while (not valid);   
        
        int bakiye;
        valid = false;
		do{
	        printf("\nBakiye : ");
	        scanf("%d", &bakiye);
	        if (bakiye <-50000 || bakiye >50000){
	        	printf("\nBakiye -50000 +50000 araliginda olmalidir!"); 
			} else {
				valid = true;
			}
        }
        while (not valid);   
        tkp.bakiye = bakiye;

		int hata;
        fseek(d1, (hno-1) * sizeof(struct takip), SEEK_SET);
        hata = fwrite (&tkp, sizeof(struct takip), 1, d1);
     
        if (hata = 0) {
           printf("\nDosyaya yazma hatasý!");
    	} else {
		   printf("\nHesap olusturuldu.");  
		}
    	
	    
        fclose(d1);
        
        printf("\nDevam etmek icin herhangi bir tusa basiniz...");  
		getch();
        
    }
    
    void hesapsil(){
    	FILE *d1;
        takip tkp;
        
        if ( (d1 = fopen("banka.dat", "r+b") ) == NULL ){
     		printf ("Dosya acilamadi...");
            //break;
            
     	}
 
        printf("Hesap Sil");

        int hno;
        bool valid = false;
		do{
	        printf("\nSilmek istediginiz hesap No : ");
	        scanf("%d", &hno);
	        if (hno <1 || hno >100){
	        	printf("\nHesap no 1-100 araliginda olmalidir!"); 
			} else {
		        fseek(d1, (hno-1) * sizeof(struct takip), SEEK_SET);
		        fread(&tkp, sizeof(struct takip), 1, d1);
		        
		        if (tkp.hesapno==-1){
		        	printf("\n%d nolu hesap daha olusturulmamis! Lutfen baska bir hesap no seciniz!", hno);
				} else {
					valid = true;
				}
			}
        }
        while (not valid);   
        tkp.hesapno = -1;
		
		int hata;
        fseek(d1, (hno-1) * sizeof(struct takip), SEEK_SET);
        hata = fwrite (&tkp, sizeof(struct takip), 1, d1);
     
        if (hata = 0) {
           printf("\nDosyaya yazma hatasý!");
    	} else {
		   printf("\nHesap silindi.");  
		}
    	
	    
        fclose(d1);
        
        printf("\nDevam etmek icin herhangi bir tusa basiniz...");  
		getch();
        
    }

    void bakiyeguncelle(){
    	FILE *d1;
        takip tkp;
        
        if ( (d1 = fopen("banka.dat", "r+b") ) == NULL ){
     		printf ("Dosya acilamadi...");
            //break;
            
     	}
 
        printf("Bakiye Guncelleme");

        int hno;
        bool valid = false;
		do{
	        printf("\nGuncellemek istediginiz hesap No : ");
	        scanf("%d", &hno);
	        if (hno <1 || hno >100){
	        	printf("\nHesap no 1-100 araliginda olmalidir!"); 
			} else {
		        fseek(d1, (hno-1) * sizeof(struct takip), SEEK_SET);
		        fread(&tkp, sizeof(struct takip), 1, d1);
		        
		        if (tkp.hesapno==-1){
		        	printf("\n%d nolu hesap daha olusturulmamis! Lutfen baska bir hesap no seciniz!", hno);
				} else {
					valid = true;
				}
			}
        }
        while (not valid);   

        int ekbakiye;
        int sbakiye;
        valid = false;
		do{
	        printf("\nBakiyeye eklenecek tutar : ");
	        scanf("%d", &ekbakiye);
	        sbakiye = tkp.bakiye + ekbakiye;
	        if (sbakiye <-50000 || sbakiye >50000){
	        	printf("\nSon bakiye -50000 +50000 araliginda olmalidir!"); 
			} else {
				valid = true;
			}
        }
        while (not valid);   
        tkp.bakiye = sbakiye;
		int hata;
        fseek(d1, (hno-1) * sizeof(struct takip), SEEK_SET);
        hata = fwrite (&tkp, sizeof(struct takip), 1, d1);
     
        if (hata = 0) {
           printf("\nDosyaya yazma hatasý!");
    	} else {
		   printf("\nHesap guncellendi.");  
		}
    	
	    
        fclose(d1);
        
        printf("\nDevam etmek icin herhangi bir tusa basiniz...");  
		getch();
        
    }

    
    void hesapgoster(){
    	FILE *d1;
        takip tkp;
        
        if ( (d1 = fopen("banka.dat", "rb") ) == NULL ){
     		printf ("Dosya acilamadi...");
            //break;
     	}
        
        printf("Hesap Bilgilerini Goster");
        int hno;
        bool valid = false;
        printf("\nHesap Numarasi : ");
        scanf("%d", &hno);
        	if (hno <1 || hno >100){
	        	printf("\nHesap no 1-100 araliginda olmalidir!"); 
			} else {
				fseek(d1, (hno-1) * sizeof(struct takip), SEEK_SET);
        		fread(&tkp, sizeof(struct takip), 1, d1);
				}	
		
        
        if (tkp.hesapno==-1){
        	printf("\n%d nolu hesap daha olusturulmamis!", hno);
		} 
			if(tkp.hesapno<1 || tkp.hesapno>100){
				printf ("\nGecersiz hesap numarasi!");
			}
			else {
	        printf("\n");
	        printf("\nHesap Numarasi : %d", tkp.hesapno);
	        printf("\nAdi            : %s", tkp.ad);
	        printf("\nSoyadi         : %s", tkp.soyad);
	        printf("\nTelefonu       : %s", tkp.telno);
	        printf("\nBakiyesi       : %d TL", tkp.bakiye);
        }
      
        fclose(d1);
        
        printf("\nDevam etmek icin herhangi bir tusa basiniz");  
		getch();
    }
    
    void butunkayitlar(){
    	FILE *d1;
    	FILE *d2;
        takip tkp;
        
        if ( (d1 = fopen("banka.dat", "rb") ) == NULL ){
     		printf ("Dosya acilamadi...");
            //break;
     	}
        
        if ( (d2 = fopen("sonuc.txt", "w") ) == NULL ){
     		printf ("Sonuc dosyasi olusturulamadi...");
            //break;
     	}
        
	    while(fread(&tkp, sizeof(struct takip), 1, d1)){
	    	if (tkp.hesapno != -1){
				fprintf (d2,"Hesap No : %3d Adi : %-10s Soyadi : %-20s Telefon : %-10s Bakiye : %7d TL\n", tkp.hesapno, tkp.ad, tkp.soyad, tkp.telno, tkp.bakiye); 
    		}
		} 
	    
        printf("\nHesap bilgileri 'sonuc.txt' dosyasina yazildi.");  
        printf("\nDevam etmek icin herhangi bir tusa basiniz");  
		getch();

        fclose(d1);
        fclose(d2);
    }
    
    void bakiyefiltrele(){
    	FILE *d1;
    	FILE *d2;
        takip tkp;
        
        if ( (d1 = fopen("banka.dat", "rb") ) == NULL ){
     		printf ("Dosya acilamadi...");
            //break;
     	}
        
        if ( (d2 = fopen("sonuc.txt", "w") ) == NULL ){
     		printf ("Sonuc dosyasi olusturulamadi...");
            //break;
     	}
        
        int minbakiye;
        int maxbakiye;
        printf("\nListelemek istediginiz MINIMUM tutari yaziniz : ");
        scanf("%d", &minbakiye);
        printf("\nListelemek istediginiz MAXIMUM tutari yaziniz : ");
        scanf("%d", &maxbakiye);
        
	    while(fread(&tkp, sizeof(struct takip), 1, d1)){
	    	if (tkp.hesapno != -1){
	    		if (tkp.bakiye > minbakiye && tkp.bakiye < maxbakiye){
					fprintf (d2,"Hesap No : %3d Adi : %-10s Soyadi : %-20s Telefon : %-10s Bakiye : %7d TL\n", tkp.hesapno, tkp.ad, tkp.soyad, tkp.telno, tkp.bakiye); 
				}
    		}
		} 
	    
        printf("\nHesap bilgileri 'sonuc.txt' dosyasina yazildi.");  
        printf("\nDevam etmek icin herhangi bir tusa basiniz");  
		getch();

        fclose(d1);
        fclose(d2);
    }
   
   
    int main()
    {
        FILE *d1;
        if ( (d1 = fopen("banka.dat", "rb") ) == NULL ) {
			dosyayarat();
		} else {
			fclose(d1);
		} 
			
		printf("--");
        int secim;
        do{
        	system("cls"); 
            
            printf("\n1-Yeni Hesap Ac");
            printf("\n2-Hesap Bakiyesi Guncelle"); 
            printf("\n3-Hesap Sil");
            printf("\n4-Hesap Bilgileri Listele");
            printf("\n5-Butun Kayitlari Listele");
            printf("\n6-Bakiye Filtrele");
			printf("\n7-Cikis");
            
            printf("\nSeciminiz : ");
			scanf("%d", &secim);
			system("cls"); 
            if(secim==1) hesapac();
            if(secim==2) bakiyeguncelle();
            if(secim==3) hesapsil();
            if(secim==4) hesapgoster();
            if(secim==5) butunkayitlar();
            if(secim==6) bakiyefiltrele();

        }
        while (secim!=7);
    }
