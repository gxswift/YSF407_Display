#include "stdint.h"
#include "GUI.h"
#include "GUI_ConfDefaults.h"
#include "GUI_Type.h"
#include "stdio.h"
#include "str.h"

#define C_UTF8	0


SET_PARAM Set;



extern GUI_CONST_STORAGE GUI_FONT GUI_FontB24;


GUI_FONT Str_Font[2];//={GUI_Font20_1,GUI_FontB24}


#if C_UTF8
	
const char *String[][2]=
{
	{"Setting","����"},
	{"Temperature","�¶�"},
	{"Single-click","����"},
	{"Double-click","˫��"},
	{"Longpress","����"},
	{"Manual","�ֶ�"},
	{"Cancel","ȡ��"},
	{"Confirm","ȷ��"},
	{"Return","����"},
	{"Visible","�ɼ�"},
	{"Start","��ʼ"},
	{"Stop","ֹͣ"},
	{"Heat","����"},
	{"Status","״̬"},
	{"Upgrade","����"},
	{"Info","��Ϣ"},
	{"Flow","����"},
	{"Water In","��ˮ"},
	{"Water Out","��ˮ"},
	{"Standby","����"},
	{"ON","��"},
	{"OFF","��"},
	{"Volume","���"},
	{"Time","ʱ��"},
	{"Chinese","����"},
	{"English","Ӣ��"},
	{"",""},
};
#else

const char *String[][2]=
{
	{"Setting","\xe8\xae\xbe\xe7\xbd\xae"},
	{"Temperature","\xe6\xb8\xa9\xe5\xba\xa6"},
	{"Single-click","\xe5\x8d\x95\xe5\x87\xbb"},
	{"Double-click","\xe5\x8f\x8c\xe5\x87\xbb"},
	{"Longpress","\xe9\x95\xbf\xe6\x8c\x89"},
	{"Manual","\xe6\x89\x8b\xe5\x8a\xa8"},
	{"Cancel","\xe5\x8f\x96\xe6\xb6\x88"},
	{"Confirm","\xe7\xa1\xae\xe8\xae\xa4"},
	{"Return","\xe8\xbf\x94\xe5\x9b\x9e"},
	{"Visible","\xe5\x8f\xaf\xe8\xa7\x81"},
	{"Start","\xe5\xbc\x80\xe5\xa7\x8b"},
	{"Stop","\xe5\x81\x9c\xe6\xad\xa2"},
	{"Heat","\xe5\x8a\xa0\xe7\x83\xad"},
	{"Status","\xe7\x8a\xb6\xe6\x80\x81"},
	{"Upgrade","\xe5\x8d\x87\xe7\xba\xa7"},
	{"Info","\xe4\xbf\xa1\xe6\x81\xaf"},
	{"Flow","\xe6\xb5\x81\xe9\x87\x8f"},
	{"Water In","\xe8\xbf\x9b\xe6\xb0\xb4"},
	{"Water Out","\xe5\x87\xba\xe6\xb0\xb4"},
	{"Standby","\xe5\xbe\x85\xe6\x9c\xba"},
	{"ON","\xe5\xbc\x80"},
	{"OFF","\xe5\x85\xb3"},
	{"Volume","\xe4\xbd\x93\xe7\xa7\xaf"},
	{"Time","\xe6\x97\xb6\xe9\x97\xb4"},
	{"Chinese","\xe4\xb8\xad\xe6\x96\x87"},
	{"English","\xe8\x8b\xb1\xe6\x96\x87"},
	{"",""},
};


#endif

GUI_FONT Get_Font(uint8_t lang)
{
	return lang?GUI_Font20_1:GUI_FontB24;
}

uint8_t Find_Str(const char *str)
{
	uint8_t i;
	for (i = 0;i < sizeof (String)/sizeof(String[0]);i++)
	{
		if (strcmp(String[i][0],str) == 0)
			break;
	}
	return i;
}









#if C_UTF8





const char *HZStr[]=

{"}?n",

	")n��",

	"SO��",

	"US?",

	"??",

	"nx?",

	"��Wb",

	"y?`",

		"_��",

		"\Pbk",

		"�go`",

		"�n�[",

		"Kbg",

		"q�?",

		"��)n",

	"e?l",

	"Am?"

};



#else

const char *HZStr[]=
{
	"\xe8\xae\xbe\xe7\xbd\xae",
	"\xe6\xb8\xa9\xe5\xba\xa6",
	"\xe4\xbd\x93\xe7\xa7\xaf",
	"\xe5\x8d\x95\xe5\x87\xbb",
	"\xe5\x8f\x8c\xe5\x87\xbb",
	"\xe7\xa1\xae\xe8\xae\xa4",
	"\xe5\x8f\x96\xe6\xb6\x88",
	"\xe7\x8a\xb6\xe6\x80\x81",
	"\xe5\xbc\x80\xe5\xa7\x8b",
	"\xe5\x81\x9c\xe6\xad\xa2",
	"\xe4\xbf\xa1\xe6\x81\xaf",
	"\xe8\xbf\x94\xe5\x9b\x9e",
	"\xe6\x89\x8b\xe5\x8a\xa8",
	"\xe5\x8a\xa0\xe7\x83\xad",
	"\xe4\xbf\x9d\xe6\xb8\xa9",
	"\xe8\xa1\xa5\xe6\xb0\xb4",
	"\xe6\xb5\x81\xe9\x87\x8f"
};







#endif
