
#ifndef INVENT_H
#define INVENT_H

#define Inventory Invents::GetInstance()

class Invents
{
public:

    Invents(){};
    ~Invents(){
      
    };

    static Invents& GetInstance()
    {
        static Invents inventv;
        return inventv;
    }

 
    float firebullet = 50;
	float airbullet = 50;
	float waterbullet = 50;
	float netbullet = 50;

   
};

#endif INVENT_H