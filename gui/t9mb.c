#include "t9mb.h"

#if 1
//"ƴ�����뷨�������б�" 
const static unsigned char PY_mb_ex_space [] = {""}; 
const static unsigned char PY_mb_ex_a[]=		{"����߹����ﹺǰ���������"}; 
const static unsigned char PY_mb_ex_ai[]=		{"���������������������������������������������"}; 
const static unsigned char PY_mb_ex_an[]=		{"������������������������������������㳧"}; 
const static unsigned char PY_mb_ex_ang[]=		{"������"}; 
const static unsigned char PY_mb_ex_ao[]=		{"���°����������ð�����������������������������"}; 
const static unsigned char PY_mb_ex_b[]=		{"���������رϱ�Ȳ���ٱ������"}; 
const static unsigned char PY_mb_ex_ba[]=		{"�Ѱ˰ɰͰΰ԰հְӰŰưǰȰʰ̰ϰа���������������"}; 
const static unsigned char PY_mb_ex_bai[]=		{"�ٰװܰڲ��ذ۰ݰ�����"}; 
const static unsigned char PY_mb_ex_ban[]=		{"���������߰����������������"}; 
const static unsigned char PY_mb_ex_bang[]=	{"���������������������"}; 
const static unsigned char PY_mb_ex_bao[]=		{"�����������������������ڱ��ٰ�����������������������������"}; 
const static unsigned char PY_mb_ex_bei[]=		{"�������������������۱������������������������������������"}; 
const static unsigned char PY_mb_ex_ben[]=		{"�����������������"}; 
const static unsigned char PY_mb_ex_beng[]=	{"�ñ������±ı����"}; 
const static unsigned char PY_mb_ex_bi []=		{"�ȱرܱձٱʱڱ۱ϱ˱ƱұǱ��رɱ̱ͱбѱӱԱֱױݷ���ذ��������ݩ��޵��������������������������������������������"}; 
const static unsigned char PY_mb_ex_bian[]=	{"��߱������ޱ�������������������������������˰�"}; 
const static unsigned char PY_mb_ex_biao[]=	{"������������������������"}; 
const static unsigned char PY_mb_ex_bie[]=		{"�������"}; 
const static unsigned char PY_mb_ex_bin[]=		{"������������������������������"}; 
const static unsigned char PY_mb_ex_bing[]=	{"����������������������������"}; 
const static unsigned char PY_mb_ex_bo[]=		{"�����������������������ز������������������������������������������������"}; 
const static unsigned char PY_mb_ex_bu[]=		{"�������������Ҳ�����������߲�����������"}; 
const static unsigned char PY_mb_ex_c[]=   {"���ɳ̳²̲ܴ޳��ҳس���᯴Ӵ˴����������Ŵβ�"}; 
const static unsigned char PY_mb_ex_ca[]=   {"��������"}; 
const static unsigned char PY_mb_ex_cai[]=   {"�ɲŲĲ˲Ʋòʲ²ǲȲ�"}; 
const static unsigned char PY_mb_ex_can[]=  {"�βвϲӲͲѲ����������"}; 
const static unsigned char PY_mb_ex_cang[]=  {"�زֲԲղ�"}; 
const static unsigned char PY_mb_ex_cao[]=   {"�ݲ۲ٲڲ��������"}; 
const static unsigned char PY_mb_ex_ce[]=   {"��߲�����"}; 
const static unsigned char PY_mb_ex_cen[]=  {"����"}; 
const static unsigned char PY_mb_ex_ceng[]= {"��������"}; 
const static unsigned char PY_mb_ex_ch[]=  {"��������³̳ǳ��س���"}; 
const static unsigned char PY_mb_ex_cha[]=  {"������������ɲ���������������������"}; 
const static unsigned char PY_mb_ex_chai[]=  {"�����٭�����"}; 
const static unsigned char PY_mb_ex_chan[]= {"��������������������������������������������������"}; 
const static unsigned char PY_mb_ex_chang[]= {"�����������������������������������������������������"}; 
const static unsigned char PY_mb_ex_chao[]=  {"�������������������½���������"}; 
const static unsigned char PY_mb_ex_che[]=   {"�����߳����������"}; 
const static unsigned char PY_mb_ex_chen[]=  {"�³��Ƴĳ������򳻳����������������������"}; 
const static unsigned char PY_mb_ex_cheng[]= {"�ɳ̳Ƴǳг˳�ʢ�ųϳȳͳγѳҳ�ة���������������������"}; 
const static unsigned char PY_mb_ex_chi[]=		{"�ֳ߳ݳԳ�سٳ��ܳճ׳ڳ۳޳�����ܯ��߳������������������������������"}; 
const static unsigned char PY_mb_ex_chong[]= {"�ֳ��س���ӿ������������"}; 
const static unsigned char PY_mb_ex_chou[]=  {"��������������ٱ������"}; 
const static unsigned char PY_mb_ex_chu[]=  {"���������������������������������ءۻ���������������������"}; 
const static unsigned char PY_mb_ex_chuai[]= {"�����������"}; 
const static unsigned char PY_mb_ex_chuan[]= {"������������������������"}; 
const static unsigned char PY_mb_ex_chuang[]={"��������������"}; 
const static unsigned char PY_mb_ex_chui[]= {"������׵��������"}; 
const static unsigned char PY_mb_ex_chun[]=  {"��������������ݻ����"}; 
const static unsigned char PY_mb_ex_chuo[]= {"����������"}; 
const static unsigned char PY_mb_ex_ci[]=  {"�˴δ̴ŴƴʴĴôǴȴɴ���������������"}; 
const static unsigned char PY_mb_ex_cong[]=  {"�ӴԴϴдѴ����������"}; 
const static unsigned char PY_mb_ex_cou[]=  {"������"}; 
const static unsigned char PY_mb_ex_cu[]=   {"�ִٴ״����������������"}; 
const static unsigned char PY_mb_ex_cuan[]=  {"�۴ڴ�����ߥ����"}; 
const static unsigned char PY_mb_ex_cui[]=  {"�ߴ����˥�޴�������������"}; 
const static unsigned char PY_mb_ex_cun[]=  {"���������"}; 
const static unsigned char PY_mb_ex_cuo[]=  {"������������������������"}; 
const static unsigned char PY_mb_ex_d[]=    {"�Ĵ�ضŶ��δ��˶��ҵԵ�絳���ȵ��ӵ����"}; 
const static unsigned char PY_mb_ex_da[]=    {"�����������������������������"}; 
const static unsigned char PY_mb_ex_dai[]=  {"�������������������������ܤ߰߾����������"}; 
const static unsigned char PY_mb_ex_dan[]=  {"��������ʯ������������������������������������������"}; 
const static unsigned char PY_mb_ex_dang[]=  {"��������������������"}; 
const static unsigned char PY_mb_ex_dao[]=   {"������������������������߶���������"}; 
const static unsigned char PY_mb_ex_de[]=   {"�ĵõصµ��"}; 
const static unsigned char PY_mb_ex_deng[]= {"�ȵƵǵ˳εŵɵ������������"}; 
const static unsigned char PY_mb_ex_di[]=   {"�ĵصڵ͵е���۵ֵεܵݵ̵ϵѵҵӵԵյٵ�ص��ڮ��ۡ��ݶ���������������������"}; 
const static unsigned char PY_mb_ex_dia[]=  {"��"}; 
const static unsigned char PY_mb_ex_dian[]=  {"������ߵ��������������������������"}; 
const static unsigned char PY_mb_ex_diao[]=  {"���������������������"}; 
const static unsigned char PY_mb_ex_die[]=  {"����������������ܦ�������������"}; 
const static unsigned char PY_mb_ex_ding[]=  {"������������������������������������"}; 
const static unsigned char PY_mb_ex_diu[]=  {"����"}; 
const static unsigned char PY_mb_ex_dong[]=  {"����������������������������������"}; 
const static unsigned char PY_mb_ex_dou[]=  {"������������������������"}; 
const static unsigned char PY_mb_ex_du[]=  {"�ȶ��������ɶŶ¶ƶٶ����öĶǶ�ܶ�������������"}; 
const static unsigned char PY_mb_ex_duan[]=  {"�϶˶ζ̶Ͷ������"}; 
const static unsigned char PY_mb_ex_dui[]=   {"�ԶӶѶض�����"}; 
const static unsigned char PY_mb_ex_dun[]=  {"�ֶܶٶ׶ضնڶ۶��������������"}; 
const static unsigned char PY_mb_ex_duo[]=  {"��ȶ��޶߶������������������������"}; 
const static unsigned char PY_mb_ex_e[]=   {"����������������������ج������ݭ��������������������"}; 
const static unsigned char PY_mb_ex_ei[]=   {"��"}; 
const static unsigned char PY_mb_ex_en[]=   {"������"}; 
const static unsigned char PY_mb_ex_er[]=   {"����������������٦���������"}; 
const static unsigned char PY_mb_ex_f[]=    {"�ַ��������뷴�Ÿ�����Ƿ⸻��"}; 
const static unsigned char PY_mb_ex_fa[]=   {"��������������������"}; 
const static unsigned char PY_mb_ex_fan[]=  {"����������������������������������ެ����������"}; 
const static unsigned char PY_mb_ex_fang[]=  {"���ŷ��÷��ķ·�������������������"}; 
const static unsigned char PY_mb_ex_fei[]=  {"�ǷʷɷѷϷηзƷ˷ȷ̷�������������������������������"}; 
const static unsigned char PY_mb_ex_fen[]=  {"�ַ۷ܷݷ�׷ҷ߷ӷԷշطٷڷ������������"}; 
const static unsigned char PY_mb_ex_feng[]=  {"����������������ٺۺ�������"}; 
const static unsigned char PY_mb_ex_fo[]=   {"��"}; 
const static unsigned char PY_mb_ex_fou[]=   {"���"}; 
const static unsigned char PY_mb_ex_fu[]=   {"���������򸺸����������������������������������𸿸��������������������������������������������ۮܽ������ݳ����߻����������������������������������������������"}; 
const static unsigned char PY_mb_ex_g[]=   {"���������߹���𹢹����ʸɹżֹȹ˹عܸ��﹫�����Ĺ����񹲸�"}; 
const static unsigned char PY_mb_ex_ga[]=   {"�и��¸����������"}; 
const static unsigned char PY_mb_ex_gai[]=   {"�ĸøǸŸƸȽ�ؤ�������"}; 
const static unsigned char PY_mb_ex_gan[]=  {"�ɸ˸иҸϸʸθѸ̸͸�Ǭ������ߦ���������������"}; 
const static unsigned char PY_mb_ex_gang[]=  {"�ոָ׸ٸڸ۸ܸԸؿ�����"}; 
const static unsigned char PY_mb_ex_gao[]=   {"�߸����ݸ޸���غھ۬޻��������"}; 
const static unsigned char PY_mb_ex_ge[]=   {"������ϸ�����Ǹ�������������ت������ܪ�������������������"}; 
const static unsigned char PY_mb_ex_gei[]=  {"��"}; 
const static unsigned char PY_mb_ex_gen[]=  {"����بݢ����"}; 
const static unsigned char PY_mb_ex_geng[]= {"�����������������������"}; 
const static unsigned char PY_mb_ex_gong[]= {"�������������칮�����������������������"}; 
const static unsigned char PY_mb_ex_gou[]=  {"�������乷������������ڸ������������������"}; 
const static unsigned char PY_mb_ex_gu[]=  {"�Ĺ̹Źǹʹ˹ɹȹ��͹¹üֹ�������������ڬ����������������������������������������"}; 
const static unsigned char PY_mb_ex_gua[]=  {"�ҹι����йѹ���ڴ�������"}; 
const static unsigned char PY_mb_ex_guai[]=  {"�ֹԹ���"}; 
const static unsigned char PY_mb_ex_guan[]= {"�عܹ۹ٹ��߹ڹݹ޹�����ݸ������������"}; 
const static unsigned char PY_mb_ex_guang[]={"������������"}; 
const static unsigned char PY_mb_ex_gui[]=  {"�������������������Ȳ���������������������"}; 
const static unsigned char PY_mb_ex_gun[]=  {"�������������"}; 
const static unsigned char PY_mb_ex_guo[]=  {"�����������й����������������������"}; 
const static unsigned char PY_mb_ex_h[]=   {"�ͻ��λƺ����ػ��身���»��úϻ���ܻغź����򺣻����"}; 
const static unsigned char PY_mb_ex_ha[]=   {"����Ϻ��"}; 
const static unsigned char PY_mb_ex_hai[]=   {"�����������������ٿ�������"}; 
const static unsigned char PY_mb_ex_han[]=   {"����������������������������������������������������������"}; 
const static unsigned char PY_mb_ex_hang[]= {"�к����������������"}; 
const static unsigned char PY_mb_ex_hao[]=   {"�úź��ĺ��ºƸ亾������޶����������"}; 
const static unsigned char PY_mb_ex_he[]=   {"�ͺϺӺκ˺պɺֺȺغǺ��źкʺѺҺԺ�ڭ�������������������"}; 
const static unsigned char PY_mb_ex_hei[]=   {"�ں���"}; 
const static unsigned char PY_mb_ex_hen[]=  {"�ܺݺۺ�"}; 
const static unsigned char PY_mb_ex_heng[]= {"����ߺ�޿������"}; 
const static unsigned char PY_mb_ex_hong[]=  {"��������������ڧݦޮް����"}; 
const static unsigned char PY_mb_ex_hou[]=  {"��������ܩ��������������"}; 
const static unsigned char PY_mb_ex_hu[]=  {"�ͻ����������������������˺�Ϸ��������������������������������������������������������"}; 
const static unsigned char PY_mb_ex_hua[]=  {"���������������������������"}; 
const static unsigned char PY_mb_ex_huai[]=  {"��������������"}; 
const static unsigned char PY_mb_ex_huan[]= {"�������������û�������������ۨۼ��ߧ������������������"}; 
const static unsigned char PY_mb_ex_huang[]= {"�ƻɻĻʻŻȻǻ˻̻ͻλϻл��������������������"}; 
const static unsigned char PY_mb_ex_hui[]=  {"��ػһӻԻ�ٻۻֻ�ݻ����黲�׻ڻܻ޻߻����ڶ����ޥ������������������������"}; 
const static unsigned char PY_mb_ex_hun[]=  {"�������ڻ������"}; 
const static unsigned char PY_mb_ex_huo[]=  {"�ͻ��������������޽߫������������"}; 
const static unsigned char PY_mb_ex_j[]=   {"���ֽ�������������ͽ��Ӿ��ҽ�׼������ϻ����ӽ̼��ż�"}; 
const static unsigned char PY_mb_ex_ji[]=   {"������������������Ǽ���ϵ��Ƽ����ʼ����ü����̼����ȼͼļ����������漪�����������������������������������������¼żɼ˽�آؽ����٥��ڵ��ܸ������ު��ߴ���������������������������������������������������������"}; 
const static unsigned char PY_mb_ex_jia[]=  {"�ӼҼܼۼ׼мټؼּڼݼμϼѼԼռ���Ю��٤ۣ������������������������������"}; 
const static unsigned char PY_mb_ex_jian[]=  {"�������������������轥�����������߼��ǳ����뽢�����������������������������������������������������������������������"}; 
const static unsigned char PY_mb_ex_jiang[]= {"������ǿ������������������������������������"}; 
const static unsigned char PY_mb_ex_jiao[]= {"�Ͻ̽��ǽнŽ�������У�����ͽ��½ѽ����������ýĽƽȽɽʽ˽�ٮ��ܴ����������������������"}; 
const static unsigned char PY_mb_ex_jie[]=  {"��׽�ӽڼҽ�ؽ��۽�ֽҽ�߽ܽԽսٽ۽ݽ޽�����뿬��ڦڵ���������������������"}; 
const static unsigned char PY_mb_ex_jin[]= {"���������񾡽�����������������������ݣ����������������������"}; 
const static unsigned char PY_mb_ex_jing[]= {"��������������������������������������������������������ݼ������������������"}; 
const static unsigned char PY_mb_ex_jiong[]= {"����������"}; 
const static unsigned char PY_mb_ex_jiu[]=  {"�;žɾ��þȾƾ������¾ľǾʾ˾̾�����������������"}; 
const static unsigned char PY_mb_ex_ju[]=   {"�߾ݾ־ٳ���۾�޾Ӿ��ؾܹ�۾ϾоѾҾԾվ׾ھ������ڪ��������������������������������������������"}; 
const static unsigned char PY_mb_ex_juan[]=  {"�������۲�������������"}; 
const static unsigned char PY_mb_ex_jue[]=   {"�������ǽž������������������ާ�������������������������޶�"}; 
const static unsigned char PY_mb_ex_jun[]=   {"�������������������������������"}; 
const static unsigned char PY_mb_ex_k[]=   {"�ɿ�����˿����ܿƿڿտ�쿼�̿���������󿹿�"}; 
const static unsigned char PY_mb_ex_ka[]=   {"��������������"}; 
const static unsigned char PY_mb_ex_kai[]=   {"�������������������������"}; 
const static unsigned char PY_mb_ex_kan[]=  {"��������������Ƕ٩ݨ������"}; 
const static unsigned char PY_mb_ex_kang[]= {"��������������������"}; 
const static unsigned char PY_mb_ex_kao[]=  {"����������������"}; 
const static unsigned char PY_mb_ex_ke[]=  {"�ɿ˿ƿ̿Ϳǿſÿºǿ����Ŀȿʿ����������������������������"}; 
const static unsigned char PY_mb_ex_ken[]= {"�Ͽпѿ���"}; 
const static unsigned char PY_mb_ex_keng[]= {"�ӿ��"}; 
const static unsigned char PY_mb_ex_kong[]= {"�׿տؿ�������"}; 
const static unsigned char PY_mb_ex_kou[]=  {"�ڿۿٿ���ޢߵ����"}; 
const static unsigned char PY_mb_ex_ku[]=  {"���ݿ�޿߿���ܥ����"}; 
const static unsigned char PY_mb_ex_kua[]=  {"������٨"}; 
const static unsigned char PY_mb_ex_kuai[]=  {"��������ۦ�������"}; 
const static unsigned char PY_mb_ex_kuan[]= {"�����"}; 
const static unsigned char PY_mb_ex_kuang[]= {"�����������ڲڿ������������"}; 
const static unsigned char PY_mb_ex_kui[]=  {"����������������������ظ���������������������������"}; 
const static unsigned char PY_mb_ex_kun[]=  {"��������������������"}; 
const static unsigned char PY_mb_ex_kuo[]=  {"��������������"}; 
const static unsigned char PY_mb_ex_l[]=   {"������������³��������¬������½����¹����·������������������������������"}; 
const static unsigned char PY_mb_ex_la[]=   {"���������������������������"}; 
const static unsigned char PY_mb_ex_lai[]=   {"���������������������"}; 
const static unsigned char PY_mb_ex_lan[]=  {"����������������������������������������"}; 
const static unsigned char PY_mb_ex_lang[]= {"��������������ݹ����������"}; 
const static unsigned char PY_mb_ex_lao[]= {"���������������������������������������"}; 
const static unsigned char PY_mb_ex_le[]=   {"����������߷����"}; 
const static unsigned char PY_mb_ex_lei[]=  {"��������������������������ڳ������������"}; 
const static unsigned char PY_mb_ex_leng[]=  {"������ܨ�"}; 
const static unsigned char PY_mb_ex_li[]=  {"��������������������������������������������������������������������تٳٵ۪����ݰ��޼߿����������������������������������������������������������"}; 
const static unsigned char PY_mb_ex_lia[]=  {"��"}; 
const static unsigned char PY_mb_ex_lian[]=  {"����������������������������������������������������"}; 
const static unsigned char PY_mb_ex_liang[]= {"����������������������ܮݹ�������"}; 
const static unsigned char PY_mb_ex_liao[]=  {"��������������������������ޤ������������"}; 
const static unsigned char PY_mb_ex_lie[]=  {"�������������������������"}; 
const static unsigned char PY_mb_ex_lin[]=  {"���������������������������������������������"}; 
const static unsigned char PY_mb_ex_ling[]= {"��������������������������������۹����������������������"}; 
const static unsigned char PY_mb_ex_liu[]=  {"������������½����������µ����������������"}; 
const static unsigned char PY_mb_ex_lo[]=  {"��"}; 
const static unsigned char PY_mb_ex_long[]=  {"��¢Ū��¡������£¤���������������"}; 
const static unsigned char PY_mb_ex_lou[]=  {"©¶¥¦§¨ª�����������������"}; 
const static unsigned char PY_mb_ex_lu[]=  {"·¼½¯¶«¬­®°±²³´µ¸¹º»¾��ߣ��������������������������������������"}; 
const static unsigned char PY_mb_ex_luan[]=  {"��������������������"}; 
const static unsigned char PY_mb_ex_lue[]=  {"�����"}; 
const static unsigned char PY_mb_ex_lun[]=  {"����������������"}; 
const static unsigned char PY_mb_ex_luo[]=   {"�����������߿������������������������������������������"}; 
const static unsigned char PY_mb_ex_lv[]=   {"��������¿�������������������������������"}; 
const static unsigned char PY_mb_ex_m[]=   {"����������÷������ëé��Īû����ôÿ����ĥ������ĶĿ߼"}; 
const static unsigned char PY_mb_ex_ma[]=   {"��ô������������ĦĨ������������"}; 
const static unsigned char PY_mb_ex_mai[]=   {"������������۽ݤ��"}; 
const static unsigned char PY_mb_ex_man[]=  {"����������������áܬ��������������"}; 
const static unsigned char PY_mb_ex_mang[]= {"æâäãåç��������"}; 
const static unsigned char PY_mb_ex_mao[]=   {"ëìðòóñèéêíîï�������������������"}; 
const static unsigned char PY_mb_ex_me[]=  {"ô��"}; 
const static unsigned char PY_mb_ex_mei[]= {"ûÿ��úùø÷��üõöýþ����������ݮ���������������"}; 
const static unsigned char PY_mb_ex_men[]=  {"�������������"}; 
const static unsigned char PY_mb_ex_meng[]=  {"��������������å������ޫ��������������"}; 
const static unsigned char PY_mb_ex_mi[]=  {"��������������������������������������������������������"}; 
const static unsigned char PY_mb_ex_mian[]=  {"����������������������������"}; 
const static unsigned char PY_mb_ex_miao[]= {"������������������������������"}; 
const static unsigned char PY_mb_ex_mie[]=  {"����ؿ�����"}; 
const static unsigned char PY_mb_ex_min[]=  {"������������������������������"}; 
const static unsigned char PY_mb_ex_ming[]=  {"��������������ڤ���������"}; 
const static unsigned char PY_mb_ex_miu[]=  {"����"}; 
const static unsigned char PY_mb_ex_mo[]=  {"��ĥû��ĩģĤ��īĦ��ĪĨðĬ�Ѻ�ġĢħĭĮįİ�����������������������"}; 
const static unsigned char PY_mb_ex_mou[]=  {"ĳıĲٰ������������"}; 
const static unsigned char PY_mb_ex_mu[]=   {"ĶĿľĸĹģĻ��ķ����ĲĴĵĺļĽ�������������"}; 
const static unsigned char PY_mb_ex_n[]=   {"����������ũ��������Ů��������ţ����ճ������"}; 
const static unsigned char PY_mb_ex_na[]=   {"��������������������������"}; 
const static unsigned char PY_mb_ex_nai[]=  {"������������ؾܵ����"}; 
const static unsigned char PY_mb_ex_nan[]=  {"������������������"}; 
const static unsigned char PY_mb_ex_nang[]= {"��߭������"}; 
const static unsigned char PY_mb_ex_nao[]=  {"����Ŭ������ث������������"}; 
const static unsigned char PY_mb_ex_ne[]=  {"������ګ"}; 
const static unsigned char PY_mb_ex_nei[]=  {"��������"}; 
const static unsigned char PY_mb_ex_nen[]=  {"���"}; 
const static unsigned char PY_mb_ex_neng[]= {"��"}; 
const static unsigned char PY_mb_ex_ni[]=  {"��������������������������٣�����������������"}; 
const static unsigned char PY_mb_ex_nian[]= {"����ճ������������إ���������"}; 
const static unsigned char PY_mb_ex_niang[]={"����"}; 
const static unsigned char PY_mb_ex_niao[]=  {"��������������"}; 
const static unsigned char PY_mb_ex_nie[]=  {"��������������ؿ����������"}; 
const static unsigned char PY_mb_ex_nin[]=  {"���"}; 
const static unsigned char PY_mb_ex_ning[]= {"����š����Ţ���������"}; 
const static unsigned char PY_mb_ex_niu[]=  {"ţŤťŦ�������"}; 
const static unsigned char PY_mb_ex_nong[]= {"ũŪŨŧٯ��"}; 
const static unsigned char PY_mb_ex_nou[]=  {"��"}; 
const static unsigned char PY_mb_ex_nu[]=  {"Ŭūŭ��������"}; 
const static unsigned char PY_mb_ex_nuan[]=  {"ů"}; 
const static unsigned char PY_mb_ex_nuo[]=   {"ŵ��ŲųŴ�������"}; 
const static unsigned char PY_mb_ex_nv[]=  {"Ů�����"}; 
const static unsigned char PY_mb_ex_nve[]=  {"Űű"}; 
const static unsigned char PY_mb_ex_o[]=  {"Ŷ���ŷżŸŹźŻ����"}; 
const static unsigned char PY_mb_ex_ou[]=  {"��ŷżŸŹźŻŽک�����"}; 
const static unsigned char PY_mb_ex_p[]=   {"��ƽ��������������Ƭ������ƷƤ����ƫ��������ƶ����"}; 
const static unsigned char PY_mb_ex_pa[]=  {"���������ǰ�žſ����������"}; 
const static unsigned char PY_mb_ex_pai[]=  {"����������������ٽ��"}; 
const static unsigned char PY_mb_ex_pan[]=  {"�����ѷ��������������������������"}; 
const static unsigned char PY_mb_ex_pang[]= {"�԰�����������������"}; 
const static unsigned char PY_mb_ex_pao[]=  {"������������������������"}; 
const static unsigned char PY_mb_ex_pei[]=  {"�����������������������������"}; 
const static unsigned char PY_mb_ex_pen[]=  {"������"}; 
const static unsigned char PY_mb_ex_peng[]= {"����������������������������ܡ�����"}; 
const static unsigned char PY_mb_ex_pi[]=  {"��Ƥ�������Ƣƣ������������ơƥƦƧƨƩا��������ۯ����ܱ��ߨ����������������������������"}; 
const static unsigned char PY_mb_ex_pian[]=  {"Ƭƫ��ƪƭ����������������"}; 
const static unsigned char PY_mb_ex_piao[]=  {"ƱƯ��Ʈư��ݳ������������"}; 
const static unsigned char PY_mb_ex_pie[]=  {"ƲƳد���"}; 
const static unsigned char PY_mb_ex_pin[]=  {"ƷƶƵƴƻƸ���������"}; 
const static unsigned char PY_mb_ex_ping[]= {"ƽ��ƿƾƻ��ƹƺƼ��ٷ�����ڢ"}; 
const static unsigned char PY_mb_ex_po[]=  {"�������÷��Ӳ�������������۶��������������"}; 
const static unsigned char PY_mb_ex_pou[]=  {"������"}; 
const static unsigned char PY_mb_ex_pu[]=   {"���������̱������ѱ��������������������������������"}; 
const static unsigned char PY_mb_ex_q[]=   {"��ǰ��Ǯ����������������ȥ��ȫ��Ⱥ����ǿ��ȡ������ȷȨ����"}; 
const static unsigned char PY_mb_ex_qi[]=  {"���������������������������������������������������������������������������ؽ��ٹ��ܻ����ݽ����ޭ��������������������������������������������"}; 
const static unsigned char PY_mb_ex_qia[]=  {"��ǡ��Ǣ٤������"}; 
const static unsigned char PY_mb_ex_qian[]= {"ǰǧǮǳǩǨǦǱǣǯ��ǴǤǥǪǫǬǭǲǵǶǷǸٻ����ܷ����ݡ������������������������"}; 
const static unsigned char PY_mb_ex_qiang[]= {"ǿ��ǹ��ǽǻǺǼǾ����������������������"}; 
const static unsigned char PY_mb_ex_qiao[]=  {"���ƿ������ǽ���������������������ȸ��ڽ�����������������"}; 
const static unsigned char PY_mb_ex_qie[]=  {"������������٤ۧ���������"}; 
const static unsigned char PY_mb_ex_qin[]=   {"����������������������������������������������"}; 
const static unsigned char PY_mb_ex_qing[]= {"��������������������������������������������������"}; 
const static unsigned char PY_mb_ex_qiong[]= {"�����������������"}; 
const static unsigned char PY_mb_ex_qiu[]=  {"������������������ٴ��������������������������"}; 
const static unsigned char PY_mb_ex_qu[]=  {"ȥ��ȡ������������Ȥ����Ȣȣ��ڰ۾��ޡ޾��������������������������"}; 
const static unsigned char PY_mb_ex_quan[]=  {"ȫȨȦȰȪȩȧȬȭȮȯڹ���������������"}; 
const static unsigned char PY_mb_ex_que[]=  {"ȷȴȱȲȳȵȶȸ�����"}; 
const static unsigned char PY_mb_ex_qun[]=  {"Ⱥȹ��"}; 
const static unsigned char PY_mb_ex_r[]=   {"������������������Ȼ��������ȼȾ������������"}; 
const static unsigned char PY_mb_ex_ran[]=  {"ȻȼȾȽ������"}; 
const static unsigned char PY_mb_ex_rang[]=  {"������ȿ�����"}; 
const static unsigned char PY_mb_ex_rao[]=   {"�����������"}; 
const static unsigned char PY_mb_ex_re[]=   {"������"}; 
const static unsigned char PY_mb_ex_ren[]=   {"���������������������������������"}; 
const static unsigned char PY_mb_ex_reng[]=  {"����"}; 
const static unsigned char PY_mb_ex_ri[]=   {"��"}; 
const static unsigned char PY_mb_ex_rong[]=  {"������������������������������"}; 
const static unsigned char PY_mb_ex_rou[]=  {"������������"}; 
const static unsigned char PY_mb_ex_ru[]=   {"����������������������޸������������"}; 
const static unsigned char PY_mb_ex_ruan[]=  {"������"}; 
const static unsigned char PY_mb_ex_rui[]=   {"��������ި����"}; 
const static unsigned char PY_mb_ex_run[]=  {"����"}; 
const static unsigned char PY_mb_ex_ruo[]=   {"����ټ��"}; 
const static unsigned char PY_mb_ex_s[]=   {"����ʱ����������ʩ������ʦ˧ɳ��ʯʷ��˵����ˮ����ʮʹ������ʵ��ʽɽ��"}; 
const static unsigned char PY_mb_ex_sa[]=    {"������ئ�������"}; 
const static unsigned char PY_mb_ex_sai[]=  {"��˼��������"}; 
const static unsigned char PY_mb_ex_san[]=  {"��ɢ��ɡ�����"}; 
const static unsigned char PY_mb_ex_sang[]=  {"ɣɥɤ�����"}; 
const static unsigned char PY_mb_ex_sao[]=   {"ɨ��ɦɧɩܣ����������"}; 
const static unsigned char PY_mb_ex_se[]=  {"ɫ��ɪɬ����"}; 
const static unsigned char PY_mb_ex_sen[]=  {"ɭ"}; 
const static unsigned char PY_mb_ex_seng[]= {"ɮ"}; 
const static unsigned char PY_mb_ex_sh[]=   {"����ɽɾ����������������ʦʼ��������������˫ˮ˭˯˰˳"}; 
const static unsigned char PY_mb_ex_sha[]=  {"ɳɱɰɶɴɯɲɵɷɼ������������������"}; 
const static unsigned char PY_mb_ex_shai[]=  {"ɫɸɹ"}; 
const static unsigned char PY_mb_ex_shan[]= {"ɽ������ɺ���µ�ɻɼɾɿ������������դ��ڨ۷��������������������������"}; 
const static unsigned char PY_mb_ex_shang[]= {"���������������������������"}; 
const static unsigned char PY_mb_ex_shao[]= {"��������������������������ۿ�����������"}; 
const static unsigned char PY_mb_ex_she[]=  {"������������������������������ߡ�������"}; 
const static unsigned char PY_mb_ex_shen[]=  {"������ʲ���������������������������ڷ��ݷ�������������"}; 
const static unsigned char PY_mb_ex_sheng[]= {"��ʤ��ʡ��ʢ��ʣʥ����������������"}; 
const static unsigned char PY_mb_ex_shi[]=   {"��ʱʮʹ��ʵʽʶ����ʯʲʾ��ʷʦʼʩʿ��ʪ��ʳʧ��������ʴʫ��ֳʰ��ʻ��ʨʬʭʸʺ��������������������������ݪ��߱������������������������"}; 
const static unsigned char PY_mb_ex_shou[]=  {"���������������������������"}; 
const static unsigned char PY_mb_ex_shu[]=  {"����������������������������������������������������������������ˡ��حٿ������������������"}; 
const static unsigned char PY_mb_ex_shua[]= {"ˢˣ�"}; 
const static unsigned char PY_mb_ex_shuai[]= {"˥˧ˤ˦�"}; 
const static unsigned char PY_mb_ex_shuan[]= {"˨˩����"}; 
const static unsigned char PY_mb_ex_shuang[]={"˫˪ˬ����"}; 
const static unsigned char PY_mb_ex_shui[]= {"ˮ˵˭˯˰"}; 
const static unsigned char PY_mb_ex_shun[]=  {"˳˱˲˴"}; 
const static unsigned char PY_mb_ex_shuo[]=  {"˵��˶˷˸����������"}; 
const static unsigned char PY_mb_ex_si[]=  {"��˼��˹˿��˾��ʳ˽��˺˻������������ٹ����������������������������"}; 
const static unsigned char PY_mb_ex_song[]=  {"����������������ڡݿ����������"}; 
const static unsigned char PY_mb_ex_sou[]=  {"����������޴�������������"}; 
const static unsigned char PY_mb_ex_su[]=  {"�����������������������������������������"}; 
const static unsigned char PY_mb_ex_suan[]=  {"�������"}; 
const static unsigned char PY_mb_ex_sui[]=  {"��������������������������ݴ��������"}; 
const static unsigned char PY_mb_ex_sun[]=  {"������ݥ������"}; 
const static unsigned char PY_mb_ex_suo[]=  {"��������ɯ�����������������������"}; 
const static unsigned char PY_mb_ex_t[]=  {"��ͬ����̷����ͯͿ��١������ͼ��ͷͨ��������ͳ̨��̫����"}; 
const static unsigned char PY_mb_ex_ta[]=  {"��������̤��̡̢̣�������������������"}; 
const static unsigned char PY_mb_ex_tai[]= {"̨̧̫̬̥̩̦̪̭ۢ޷߾������������"}; 
const static unsigned char PY_mb_ex_tan[]= {"̸̼̽̿��̴̵̶̷̹̰̲̮̯̱̳̺̻̾۰����������"}; 
const static unsigned char PY_mb_ex_tang[]= {"����������������������������������������������"}; 
const static unsigned char PY_mb_ex_tao[]= {"����������������������ػ߶��������"}; 
const static unsigned char PY_mb_ex_te[]=  {"��߯����"}; 
const static unsigned char PY_mb_ex_teng[]= {"����������"}; 
const static unsigned char PY_mb_ex_ti[]= {"�����������������������������������������������"}; 
const static unsigned char PY_mb_ex_tian[]=  {"��������������������������"}; 
const static unsigned char PY_mb_ex_tiao[]= {"������������٬�����������������"}; 
const static unsigned char PY_mb_ex_tie[]= {"����������"}; 
const static unsigned char PY_mb_ex_ting[]= {"��ͣͥͦ͢����ͤͧ͡���������������"}; 
const static unsigned char PY_mb_ex_tong[]= {"ͬͨͳͭʹͲͯͰ����ͩͪͫͮͱ١���������������"}; 
const static unsigned char PY_mb_ex_tou[]=  {"ͷͶ͸͵����"}; 
const static unsigned char PY_mb_ex_tu[]=  {"ͼ��ͻ;ͽ͹Ϳ������ͺܢݱ������"}; 
const static unsigned char PY_mb_ex_tuan[]=  {"���������ͼ��"}; 
const static unsigned char PY_mb_ex_tui[]=  {"������������߯��"}; 
const static unsigned char PY_mb_ex_tun[]=  {"�����������������"}; 
const static unsigned char PY_mb_ex_tuo[]=   {"���������ֶ���������������ر٢������������������������"}; 
const static unsigned char PY_mb_ex_w[]=  {"Ϊ����������κ��Τ������������������λ��ί��������������Χ����"}; 
const static unsigned char PY_mb_ex_wa[]=  {"���ڰ����������������"}; 
const static unsigned char PY_mb_ex_wai[]=  {"������"}; 
const static unsigned char PY_mb_ex_wan[]=  {"����������������������������������������ܹݸ������������"}; 
const static unsigned char PY_mb_ex_wang[]=  {"����������������â�������������"}; 
const static unsigned char PY_mb_ex_wei[]=  {"ΪλίΧάΨ��΢ΰδ��Σβνιζθκα��ΥΤηγΡΦΩΫέήεμξο������������ޱ���������������������������������"}; 
const static unsigned char PY_mb_ex_wen[]=  {"�������������������������������"}; 
const static unsigned char PY_mb_ex_weng[]=  {"��������޳"}; 
const static unsigned char PY_mb_ex_wo[]=  {"��������������������ݫ���������"}; 
const static unsigned char PY_mb_ex_wu[]=  {"�������������������������������������������������������������أ����������������������������������������������"}; 
const static unsigned char PY_mb_ex_x[]=  {"ѧ������������ФѦ�ܽ���ϰ��С������Щ��������ϵϯ������������"}; 
const static unsigned char PY_mb_ex_xi[]=  {"ϵϯ��ϰϸ����ϲϴϳϡϷ϶ϣϢϮ��ϩ��ϤϧϪ����������������ϥϦϨϫϬϭϱ������ۭ��ݾ������������������������������������������������������������"}; 
const static unsigned char PY_mb_ex_xia[]=  {"��������ϼ��ϹϺϻϽϾϿ���������������������"}; 
const static unsigned char PY_mb_ex_xian[]= {"���������޼���������������ϴ����ϳ����������������������������ݲ޺����������������������������"}; 
const static unsigned char PY_mb_ex_xiang[]= {"���������������罵������������������������ܼ��������������"}; 
const static unsigned char PY_mb_ex_xiao[]= {"С����ЧЦУ������ФТ������������Х�����������������������"}; 
const static unsigned char PY_mb_ex_xie[]=  {"Щ��дблЭеҶѪжмЬЪавзйк��ШЫЮЯги��������ޯߢ�����������������"}; 
const static unsigned char PY_mb_ex_xin[]=  {"������по��Ѱ��н����ضܰ������"}; 
const static unsigned char PY_mb_ex_xing[]= {"������������ʡ������������������������ߩ����"}; 
const static unsigned char PY_mb_ex_xiong[]= {"��������������ܺ"}; 
const static unsigned char PY_mb_ex_xiu[]=  {"�������������޳���������������������"}; 
const static unsigned char PY_mb_ex_xu[]=   {"����������������������������������������ڼ����ޣ�������������������"}; 
const static unsigned char PY_mb_ex_xuan[]=  {"ѡ��������ȯ����ѢѣѤ������������������������������"}; 
const static unsigned char PY_mb_ex_xue[]=  {"ѧѪ��ѩѨѥѦ���������"}; 
const static unsigned char PY_mb_ex_xun[]=  {"ѵѮѸѶѰѭѲ�翣ѫѬѯѱѳѴѷ��ۨ����ަ޹�����������������"}; 
const static unsigned char PY_mb_ex_y[]=    {"һ����������Ҧ��Ԭ���������Ҷ��������Ҫ����Ҳ��������ѹԱ��������ԭ����"}; 
const static unsigned char PY_mb_ex_ya[]=   {"ѹ��ѽ��ѿ����ѼƥѺѻѾ������������������������������"}; 
const static unsigned char PY_mb_ex_yan[]=   {"����������������������������������Ǧ����������������������������������������ٲ��������۱۳ܾ�����������������������������������������"}; 
const static unsigned char PY_mb_ex_yang[]=  {"������������������������������������������������"}; 
const static unsigned char PY_mb_ex_yao[]=  {"ҪҩԼҡ��ҧ��ҫ�ս�ű����ҢңҤҥҦҨԿزسߺ������������������������"}; 
const static unsigned char PY_mb_ex_ye[]=   {"ҲҵҳҶҺҹҰүұа����ҬҭҮҴҷҸק��������������"}; 
const static unsigned char PY_mb_ex_yi[]=   {"һ����������ҽ��������������������������������������������ҼҾҿ��������������������������������������������������٫ڱ����ܲ����޲������߽߮�����������������������������������������������������������������"}; 
const static unsigned char PY_mb_ex_yin[]=  {"������ӡ��������������������������ط۴����ܧ���������������������"}; 
const static unsigned char PY_mb_ex_ying[]= {"ӦӰӲӪӢӳӭӣӤӥӧӨөӫӬӮӯӱ��۫����ݺ��������������������������"}; 
const static unsigned char PY_mb_ex_yo[]=  {"��Ӵ�"}; 
const static unsigned char PY_mb_ex_yong[]=  {"������ӵӿӼӹӶӷӸӺӻӽӾ��ٸ��ܭ�����������"}; 
const static unsigned char PY_mb_ex_you[]=  {"��������������������������������������������٧ݬݯݵ��������������������������������"}; 
const static unsigned char PY_mb_ex_yu[]=  {"����������������Ԥ����������������������εξ������������������������������������������ԡԢԣԥԦ��خع��ٶ���������������������������������������������������������������������������������"}; 
const static unsigned char PY_mb_ex_yuan[]= {"ԱԭԲԴԪԶԸԺԵԮ԰ԹԧԨԩԫԬԯԳԷ��ܫܾ��������������������"}; 
const static unsigned char PY_mb_ex_yue[]=  {"��˵ԽԼ��ԾԻ��Կ����������������"}; 
const static unsigned char PY_mb_ex_yun[]=  {"��Ա���Ⱦ�������������������۩ܿ�������������"}; 
const static unsigned char PY_mb_ex_z[]=   {"����������������֣����������ף��ׯ��ղ�����չ��ս����֮��������ֻ������ָ"}; 
const static unsigned char PY_mb_ex_za[]=   {"����������զ��"}; 
const static unsigned char PY_mb_ex_zai[]=   {"��������������������"}; 
const static unsigned char PY_mb_ex_zan[]=   {"���������������������"}; 
const static unsigned char PY_mb_ex_zang[]=  {"�������������"}; 
const static unsigned char PY_mb_ex_zao[]= {"������������������������������"}; 
const static unsigned char PY_mb_ex_ze[]=  {"���������զ�����������������"}; 
const static unsigned char PY_mb_ex_zei[]= {"��"}; 
const static unsigned char PY_mb_ex_zen[]=  {"����"}; 
const static unsigned char PY_mb_ex_zeng[]=  {"����������������"}; 
const static unsigned char PY_mb_ex_zh[]=  {"��ըժծսչ������������������������֮����ֻ��������סץתר׫׬װ״׼"}; 
const static unsigned char PY_mb_ex_zha[]=  {"����ըբա����������գդեզէթ����߸��������������"}; 
const static unsigned char PY_mb_ex_zhai[]=  {"կ����ժխի�Լ�լծ���"}; 
const static unsigned char PY_mb_ex_zhan[]= {"սչվռճ��հձղմյնշոպջտ�������"}; 
const static unsigned char PY_mb_ex_zhang[]={"����������������������������������۵��������"}; 
const static unsigned char PY_mb_ex_zhao[]=  {"�������г�����צ�����׳�����گ��������"}; 
const static unsigned char PY_mb_ex_zhe[]=  {"������������������������ߡ��������������"}; 
const static unsigned char PY_mb_ex_zhen[]=  {"������������������������������������������������������������"}; 
const static unsigned char PY_mb_ex_zheng[]= {"��������֤����֢��֣����������֡ں��������"}; 
const static unsigned char PY_mb_ex_zhi[]=   {"֮����ֻ��ֱָֹ֧֯����־ֵ֪ʶְֲִֽ��ֳ֦֬����֫��ַ��ֶֺּֿ֥֭֨֩��������������ش��ۤ���������������������������������������������������������������"}; 
const static unsigned char PY_mb_ex_zhong[]= {"����������������������ڣ���������"}; 
const static unsigned char PY_mb_ex_zhou[]=  {"����������������������������ݧ����������������"}; 
const static unsigned char PY_mb_ex_zhu[]=  {"��ע��ס������������������פ��ף��������������������������٪ۥ����������������������������������"}; 
const static unsigned char PY_mb_ex_zhua[]=  {"ץצ��"}; 
const static unsigned char PY_mb_ex_zhuai[]= {"תҷק��"}; 
const static unsigned char PY_mb_ex_zhuan[]= {"תר��ש׫׬׭�������"}; 
const static unsigned char PY_mb_ex_zhuang[]={"װ״׳ׯײ��׮ױ����"}; 
const static unsigned char PY_mb_ex_zhui[]=  {"׷׶׵׸׹׺�����"}; 
const static unsigned char PY_mb_ex_zhun[]=  {"׼��׻���"}; 
const static unsigned char PY_mb_ex_zhuo[]=  {"����׽����׾׿������������پ��ߪ�������������"}; 
const static unsigned char PY_mb_ex_zi[]=  {"����������������֨��������������������������������������������������������"}; 
const static unsigned char PY_mb_ex_zong[]=  {"����������������������"}; 
const static unsigned char PY_mb_ex_zou[]=  {"������������۸����"}; 
const static unsigned char PY_mb_ex_zu[]=  {"����������������������"}; 
const static unsigned char PY_mb_ex_zuan[]=  {"��׬��߬����"}; 
const static unsigned char PY_mb_ex_zui[]=  {"������Ѿ���ީ"}; 
const static unsigned char PY_mb_ex_zun[]=  {"����ߤ����"}; 
const static unsigned char PY_mb_ex_zuo[]=  {"������������������������������������"}; 

/*���������ѯ���*/
#endif

#if 1
const T9EN_IDX t9EN_ex_index[] = {
		{"2","abcABC"},
		{"3","defDEF"},
		{"4","ghiGHI"},
		{"5","jklJKL"},
		{"6","mnoMNO"},
		{"7","pqrsPQRS"},
		{"8","tuvTUV"},
		{"9","wxyzWXYZ"}
};
#endif

#if 1
const T9PY_IDX t9PY_ex_index[] ={
				{"2","a",PY_mb_ex_a}, 
				{"2","b",PY_mb_ex_b},
				{"2","c",PY_mb_ex_c},
				{"3","d",PY_mb_ex_d}, 
				{"3","e",PY_mb_ex_e}, 
				{"3","f",PY_mb_ex_f}, 
				{"4","g",PY_mb_ex_g}, 
				{"4","h",PY_mb_ex_h},
				{"5","j",PY_mb_ex_j}, 
				{"5","k",PY_mb_ex_k}, 
				{"5","l",PY_mb_ex_l}, 
				{"6","m",PY_mb_ex_m}, 
				{"6","n",PY_mb_ex_n}, 
				{"6","o",PY_mb_ex_o}, 
				{"7","p",PY_mb_ex_p}, 
				{"7","q",PY_mb_ex_q}, 
				{"7","r",PY_mb_ex_r}, 
				{"7","s",PY_mb_ex_s}, 
				{"8","t",PY_mb_ex_t}, 
				{"9","w",PY_mb_ex_w},
				{"9","x",PY_mb_ex_x}, 
				{"9","y",PY_mb_ex_y}, 
				{"9","z",PY_mb_ex_z}, 
				{"22","ba",PY_mb_ex_ba},
				{"22","ca",PY_mb_ex_ca},
				{"23","ce",PY_mb_ex_ce},
				{"23","be",PY_mb_ex_bei},
				{"24","ai",PY_mb_ex_ai},
				{"24","bi",PY_mb_ex_bi},
				{"24","ch",PY_mb_ex_ch},
				{"24","ci",PY_mb_ex_ci}, 
				{"26","co",PY_mb_ex_cou},
				{"26","bo",PY_mb_ex_bo},
				{"26","an",PY_mb_ex_an},
				{"26","ao",PY_mb_ex_ao},
				{"28","bu",PY_mb_ex_bu},
				{"28","cu",PY_mb_ex_cu}, 
				{"32","da",PY_mb_ex_da}, 
				{"32","fa",PY_mb_ex_fa}, 
				{"33","de",PY_mb_ex_de}, 
				{"33","fe",PY_mb_ex_fei}, 
				{"34","di",PY_mb_ex_di}, 
				{"34","ei",PY_mb_ex_ei}, 
				{"36","en",PY_mb_ex_en}, 
				{"36","fo",PY_mb_ex_fo}, 
				{"37","er",PY_mb_ex_er}, 
				{"36","do",PY_mb_ex_dou}, 
				{"38","du",PY_mb_ex_du}, 
				{"38","fu",PY_mb_ex_fu}, 
				{"42","ga",PY_mb_ex_ga}, 
				{"42","ha",PY_mb_ex_ha}, 
				{"43","ge",PY_mb_ex_ge}, 
				{"43","he",PY_mb_ex_he}, 
				{"46","go",PY_mb_ex_gou}, 
				{"46","ho",PY_mb_ex_hou}, 
				{"48","gu",PY_mb_ex_gu}, 
				{"48","hu",PY_mb_ex_hu}, 
				{"52","ka",PY_mb_ex_ka}, 
				{"52","la",PY_mb_ex_la}, 
				{"53","le",PY_mb_ex_le}, 
				{"53","ke",PY_mb_ex_ke}, 
				{"54","ji",PY_mb_ex_ji}, 
				{"54","li",PY_mb_ex_li}, 
				{"56","ko",PY_mb_ex_kou}, 
				{"56","lo",PY_mb_ex_lo}, 
				{"58","lu",PY_mb_ex_lu}, 
				{"58","lv",PY_mb_ex_lv},
				{"58","ju",PY_mb_ex_ju}, 
				{"58","ku",PY_mb_ex_ku}, 
				{"62","ma",PY_mb_ex_ma}, 
				{"62","na",PY_mb_ex_na}, 
				{"63","me",PY_mb_ex_me}, 
				{"63","ne",PY_mb_ex_ne}, 
				{"64","mi",PY_mb_ex_mi}, 
				{"64","ni",PY_mb_ex_ni}, 
				{"66","mo",PY_mb_ex_mo},
				{"66","no",PY_mb_ex_nou}, 
				{"68","mu",PY_mb_ex_mu}, 
				{"68","nu",PY_mb_ex_nu}, 
				{"68","nv",PY_mb_ex_nv}, 
				{"68","ou",PY_mb_ex_ou}, 
				{"72","pa",PY_mb_ex_pa}, 
				{"72","pe",PY_mb_ex_pei}, 
				{"72","ra",PY_mb_ex_ran}, 
				{"72","sa",PY_mb_ex_sa}, 
				{"73","re",PY_mb_ex_re}, 
				{"73","se",PY_mb_ex_se}, 
				{"74","pi",PY_mb_ex_pi}, 
				{"74","qi",PY_mb_ex_qi}, 
				{"74","ri",PY_mb_ex_ri}, 
				{"74","sh",PY_mb_ex_sh}, 
				{"74","si",PY_mb_ex_si}, 
				{"76","so",PY_mb_ex_sou},
				{"76","po",PY_mb_ex_po}, 
				{"76","ro",PY_mb_ex_rou}, 
				{"78","pu",PY_mb_ex_pu}, 
				{"78","qu",PY_mb_ex_qu}, 
				{"78","ru",PY_mb_ex_ru}, 
				{"78","su",PY_mb_ex_su}, 
				{"82","ta",PY_mb_ex_ta}, 
				{"83","te",PY_mb_ex_te}, 
				{"84","ti",PY_mb_ex_ti}, 
				{"86","to",PY_mb_ex_tou}, 
				{"88","tu",PY_mb_ex_tu}, 
				{"92","wa",PY_mb_ex_wa}, 
				{"92","ya",PY_mb_ex_ya}, 
				{"92","za",PY_mb_ex_za}, 
				{"93","ze",PY_mb_ex_ze}, 
				{"93","ye",PY_mb_ex_ye}, 
				{"94","yi",PY_mb_ex_yi}, 
				{"94","xi",PY_mb_ex_xi}, 
				{"94","zh",PY_mb_ex_zh}, 
				{"94","zi",PY_mb_ex_zi}, 
				{"96","zo",PY_mb_ex_zou}, 
				{"96","wo",PY_mb_ex_wo}, 
				{"96","yo",PY_mb_ex_yo}, 
				{"98","wu",PY_mb_ex_wu}, 
				{"98","xu",PY_mb_ex_xu}, 
				{"98","yu",PY_mb_ex_yu}, 
				{"98","zu",PY_mb_ex_zu}, 
				{"224","bai",PY_mb_ex_bai},
				{"224","cai",PY_mb_ex_cai},
				{"226","can",PY_mb_ex_can},
				{"226","cao",PY_mb_ex_cao},
				{"226","ban",PY_mb_ex_ban},
				{"226","bao",PY_mb_ex_bao},
				{"234","bei",PY_mb_ex_bei},
				{"236","ben",PY_mb_ex_ben},
				{"236","cen",PY_mb_ex_cen},
				{"242","bia",PY_mb_ex_bian},
				{"242","cha",PY_mb_ex_cha},
				{"243","che",PY_mb_ex_che},
				{"243","bie",PY_mb_ex_bie},
				{"244","chi",PY_mb_ex_chi},
				{"246","bin",PY_mb_ex_bin},
				{"246","cho",PY_mb_ex_chou},
				{"248","chu",PY_mb_ex_chu},
				{"264","ang",PY_mb_ex_ang},
				{"266","con",PY_mb_ex_cong},
				{"268","cou",PY_mb_ex_cou}, 
				{"282","cua",PY_mb_ex_cuan}, 
				{"284","cui",PY_mb_ex_cui}, 
				{"286","cun",PY_mb_ex_cun}, 
				{"286","cuo",PY_mb_ex_cuo},
				{"324","dai",PY_mb_ex_dai}, 
				{"326","dan",PY_mb_ex_dan}, 
				{"326","dao",PY_mb_ex_dao}, 
				{"326","fan",PY_mb_ex_fan}, 
				{"334","fei",PY_mb_ex_fei}, 
				{"336","fen",PY_mb_ex_fen}, 
				{"336","den",PY_mb_ex_deng},
				{"342","dia",PY_mb_ex_dia}, 
				{"343","die",PY_mb_ex_die}, 
				{"346","din",PY_mb_ex_ding},
				{"348","diu",PY_mb_ex_diu}, 
				{"366","don",PY_mb_ex_dong}, 
				{"368","dou",PY_mb_ex_dou}, 
				{"368","fou",PY_mb_ex_fou}, 
				{"382","dua",PY_mb_ex_duan}, 
				{"384","dui",PY_mb_ex_dui}, 
				{"386","dun",PY_mb_ex_dun}, 
				{"386","duo",PY_mb_ex_duo}, 
				{"424","gai",PY_mb_ex_gai}, 
				{"424","hai",PY_mb_ex_hai}, 
				{"426","han",PY_mb_ex_han}, 
				{"426","gan",PY_mb_ex_gan}, 
				{"426","gao",PY_mb_ex_gao}, 
				{"426","hao",PY_mb_ex_hao}, 
				{"434","hei",PY_mb_ex_hei}, 
				{"434","gei",PY_mb_ex_gei}, 
				{"436","gen",PY_mb_ex_gen}, 
				{"436","hen",PY_mb_ex_hen}, 
				{"466","gon",PY_mb_ex_gong}, 
				{"466","hon",PY_mb_ex_hong}, 
				{"468","gou",PY_mb_ex_gou}, 
				{"468","hou",PY_mb_ex_hou}, 
				{"482","hua",PY_mb_ex_hua}, 
				{"482","gua",PY_mb_ex_gua}, 
				{"484","gui",PY_mb_ex_gui}, 
				{"484","hui",PY_mb_ex_hui}, 
				{"486","hun",PY_mb_ex_hun}, 
				{"486","huo",PY_mb_ex_huo}, 
				{"486","gun",PY_mb_ex_gun}, 
				{"486","guo",PY_mb_ex_guo}, 
				{"524","kai",PY_mb_ex_kai}, 
				{"524","lai",PY_mb_ex_lai}, 
				{"526","lan",PY_mb_ex_lan}, 
				{"526","kan",PY_mb_ex_kan}, 
				{"526","kao",PY_mb_ex_kao}, 
				{"526","lao",PY_mb_ex_lao}, 
				{"534","lei",PY_mb_ex_lei}, 
				{"536","len",PY_mb_ex_leng}, 
				{"536","ken",PY_mb_ex_ken}, 
				{"542","jia",PY_mb_ex_jia}, 
				{"542","lia",PY_mb_ex_lia}, 
				{"543","jie",PY_mb_ex_jie}, 
				{"543","lie",PY_mb_ex_lie}, 
				{"546","lin",PY_mb_ex_lin}, 
				{"546","jin",PY_mb_ex_jin}, 
				{"546","jio",PY_mb_ex_jiong}, 
				{"548","jiu",PY_mb_ex_jiu}, 
				{"548","liu",PY_mb_ex_liu}, 
				{"566","lon",PY_mb_ex_long}, 
				{"566","kon",PY_mb_ex_kong}, 
				{"568","kou",PY_mb_ex_kou}, 
				{"568","lou",PY_mb_ex_lou}, 
				{"582","lua",PY_mb_ex_luan}, 
				{"582","kua",PY_mb_ex_kua}, 
				{"582","jua",PY_mb_ex_juan}, 
				{"583","jue",PY_mb_ex_jue}, 
				{"583","lue",PY_mb_ex_lue}, 
				{"584","kui",PY_mb_ex_kui}, 
				{"586","lun",PY_mb_ex_lun}, 
				{"586","luo",PY_mb_ex_luo}, 
				{"586","kun",PY_mb_ex_kun}, 
				{"586","kuo",PY_mb_ex_kuo}, 
				{"586","jun",PY_mb_ex_jun}, 
				{"624","mai",PY_mb_ex_mai}, 
				{"624","nai",PY_mb_ex_nai}, 
				{"626","nan",PY_mb_ex_nan}, 
				{"626","man",PY_mb_ex_man}, 
				{"626","mao",PY_mb_ex_mao}, 
				{"626","nao",PY_mb_ex_nao}, 
				{"634","nei",PY_mb_ex_nei}, 
				{"634","mei",PY_mb_ex_mei}, 
				{"636","nen",PY_mb_ex_nen}, 
				{"636","men",PY_mb_ex_men}, 
				{"642","mia",PY_mb_ex_mian}, 
				{"642","nia",PY_mb_ex_nian}, 
				{"643","mie",PY_mb_ex_mie}, 
				{"643","nie",PY_mb_ex_nie}, 
				{"646","nin",PY_mb_ex_nin}, 
				{"646","min",PY_mb_ex_min}, 
				{"648","miu",PY_mb_ex_miu}, 
				{"648","niu",PY_mb_ex_niu}, 
				{"666","non",PY_mb_ex_nong}, 
				{"668","mou",PY_mb_ex_mou}, 
				{"668","nou",PY_mb_ex_nou}, 
				{"682","nua",PY_mb_ex_nuan}, 
				{"683","nve",PY_mb_ex_nve}, 
				{"686","nuo",PY_mb_ex_nuo}, 
				{"724","pai",PY_mb_ex_pai}, 
				{"734","pei",PY_mb_ex_pei}, 
				{"724","sai",PY_mb_ex_sai}, 
				{"726","san",PY_mb_ex_san}, 
				{"726","pan",PY_mb_ex_pan}, 
				{"726","pao",PY_mb_ex_pao}, 
				{"736","pen",PY_mb_ex_pen}, 
				{"726","ran",PY_mb_ex_ran}, 
				{"726","rao",PY_mb_ex_rao}, 
				{"726","sao",PY_mb_ex_sao},
				{"736","sen",PY_mb_ex_sen}, 
				{"736","ren",PY_mb_ex_ren}, 
				{"742","pia",PY_mb_ex_pian}, 
				{"742","qia",PY_mb_ex_qia}, 
				{"742","sha",PY_mb_ex_sha}, 
				{"743","pie",PY_mb_ex_pie}, 
				{"743","qie",PY_mb_ex_qie}, 
				{"743","she",PY_mb_ex_she}, 
				{"744","shi",PY_mb_ex_shi}, 
				{"748","shu",PY_mb_ex_shu}, 
				{"746","qin",PY_mb_ex_qin}, 
				{"746","pin",PY_mb_ex_pin}, 
				{"746","qio",PY_mb_ex_qiong}, 
				{"746","sho",PY_mb_ex_shou}, 
				{"748","qiu",PY_mb_ex_qiu}, 
				{"766","ron",PY_mb_ex_rong}, 
				{"768","pou",PY_mb_ex_pou}, 
				{"768","rou",PY_mb_ex_rou}, 
				{"766","son",PY_mb_ex_song},
				{"768","sou",PY_mb_ex_sou},
				{"782","sua",PY_mb_ex_suan}, 
				{"782","rua",PY_mb_ex_ruan}, 
				{"782","qua",PY_mb_ex_quan}, 
				{"783","que",PY_mb_ex_que}, 
				{"784","rui",PY_mb_ex_rui}, 
				{"784","sui",PY_mb_ex_sui}, 
				{"786","sun",PY_mb_ex_sun}, 
				{"786","suo",PY_mb_ex_suo}, 
				{"786","run",PY_mb_ex_run}, 
				{"786","ruo",PY_mb_ex_ruo}, 
				{"786","qun",PY_mb_ex_qun}, 
				{"824","tai",PY_mb_ex_tai}, 
				{"826","tan",PY_mb_ex_tan}, 
				{"826","tao",PY_mb_ex_tao}, 
				{"836","ten",PY_mb_ex_teng}, 
				{"842","tia",PY_mb_ex_tian}, 
				{"843","tie",PY_mb_ex_tie}, 
				{"846","tin",PY_mb_ex_ting}, 
				{"866","ton",PY_mb_ex_tong}, 
				{"868","tou",PY_mb_ex_tou}, 
				{"882","tua",PY_mb_ex_tuan}, 
				{"884","tui",PY_mb_ex_tui}, 
				{"886","tun",PY_mb_ex_tun}, 
				{"886","tuo",PY_mb_ex_tuo},
				{"924","wai",PY_mb_ex_wai}, 
				{"924","zai",PY_mb_ex_zai}, 
				{"926","zan",PY_mb_ex_zan}, 
				{"926","wan",PY_mb_ex_wan}, 
				{"926","yan",PY_mb_ex_yan}, 
				{"926","yao",PY_mb_ex_yao}, 
				{"926","zao",PY_mb_ex_zao}, 
				{"934","zei",PY_mb_ex_zei}, 
				{"934","wei",PY_mb_ex_wei}, 
				{"936","zen",PY_mb_ex_zen}, 
				{"936","wen",PY_mb_ex_wen}, 
				{"942","xia",PY_mb_ex_xia}, 
				{"942","zha",PY_mb_ex_zha}, 
				{"943","xie",PY_mb_ex_xie}, 
				{"943","zhe",PY_mb_ex_zhe}, 
				{"944","zhi",PY_mb_ex_zhi}, 
				{"946","zho",PY_mb_ex_zhou}, 
				{"946","xin",PY_mb_ex_xin}, 
				{"946","xio",PY_mb_ex_xiong}, 
				{"946","yin",PY_mb_ex_yin}, 
				{"948","xiu",PY_mb_ex_xiu}, 
				{"948","zhu",PY_mb_ex_zhu}, 
				{"966","yon",PY_mb_ex_yong}, 
				{"966","zon",PY_mb_ex_zong}, 
				{"968","you",PY_mb_ex_you}, 
				{"968","zou",PY_mb_ex_zou}, 
				{"982","zua",PY_mb_ex_zuan}, 
				{"982","yua",PY_mb_ex_yuan}, 
				{"982","xua",PY_mb_ex_xuan}, 
				{"983","xue",PY_mb_ex_xue}, 
				{"983","yue",PY_mb_ex_yue}, 
				{"984","zui",PY_mb_ex_zui}, 
				{"986","zun",PY_mb_ex_zun}, 
				{"986","zuo",PY_mb_ex_zuo}, 
				{"986","yun",PY_mb_ex_yun}, 
				{"986","xun",PY_mb_ex_xun}, 
				{"2264","bang",PY_mb_ex_bang},
				{"2364","beng",PY_mb_ex_beng},
				{"2426","bian",PY_mb_ex_bian},
				{"2426","biao",PY_mb_ex_biao},
				{"2464","bing",PY_mb_ex_bing},
				{"2264","cang",PY_mb_ex_cang},
				{"2364","ceng",PY_mb_ex_ceng},
				{"2424","chai",PY_mb_ex_chai},
				{"2426","chan",PY_mb_ex_chan},
				{"2426","chao",PY_mb_ex_chao},
				{"2436","chen",PY_mb_ex_chen},				
				{"2466","chon",PY_mb_ex_chong},
				{"2468","chou",PY_mb_ex_chou},
				{"2482","chua",PY_mb_ex_chuai},
				{"2484","chui",PY_mb_ex_chui},
				{"2486","chun",PY_mb_ex_chun},
				{"2486","chuo",PY_mb_ex_chuo},				
				{"2664","cong",PY_mb_ex_cong},
				{"2826","cuan",PY_mb_ex_cuan},
				{"3264","dang",PY_mb_ex_dang}, 
				{"3264","fang",PY_mb_ex_fang}, 
				{"3364","feng",PY_mb_ex_feng}, 
				{"3364","deng",PY_mb_ex_deng}, 
				{"3426","dian",PY_mb_ex_dian}, 
				{"3426","diao",PY_mb_ex_diao}, 
				{"3464","ding",PY_mb_ex_ding}, 
				{"3664","dong",PY_mb_ex_dong}, 
				{"3826","duan",PY_mb_ex_duan}, 
				{"4264","gang",PY_mb_ex_gang}, 
				{"4364","geng",PY_mb_ex_geng}, 
				{"4664","gong",PY_mb_ex_gong}, 
				{"4824","guai",PY_mb_ex_guai}, 
				{"4826","guan",PY_mb_ex_guan}, 
				{"4264","hang",PY_mb_ex_hang}, 
				{"4364","heng",PY_mb_ex_heng}, 
				{"4664","hong",PY_mb_ex_hong}, 
				{"4824","huai",PY_mb_ex_huai}, 
				{"4826","huan",PY_mb_ex_huan},
				{"5264","kang",PY_mb_ex_kang}, 
				{"5264","lang",PY_mb_ex_lang}, 
				{"5364","leng",PY_mb_ex_leng}, 
				{"5364","keng",PY_mb_ex_keng}, 
				{"5426","lian",PY_mb_ex_lian}, 
				{"5426","liao",PY_mb_ex_liao}, 
				{"5426","jian",PY_mb_ex_jian}, 
				{"5426","jiao",PY_mb_ex_jiao}, 
				{"5464","jing",PY_mb_ex_jing}, 
				{"5464","ling",PY_mb_ex_ling}, 
				{"5466","jion",PY_mb_ex_jiong}, 
				{"5664","long",PY_mb_ex_long}, 
				{"5664","kong",PY_mb_ex_kong}, 
				{"5824","kuai",PY_mb_ex_kuai}, 
				{"5826","kuan",PY_mb_ex_kuan}, 
				{"5826","luan",PY_mb_ex_luan}, 
				{"5826","juan",PY_mb_ex_juan}, 
				{"6264","mang",PY_mb_ex_mang}, 
				{"6264","nang",PY_mb_ex_nang}, 
				{"6364","meng",PY_mb_ex_meng}, 
				{"6364","neng",PY_mb_ex_neng}, 
				{"6426","mian",PY_mb_ex_mian}, 
				{"6426","miao",PY_mb_ex_miao}, 
				{"6426","nian",PY_mb_ex_nian}, 
				{"6426","niao",PY_mb_ex_niao}, 
				{"6464","ming",PY_mb_ex_ming}, 
				{"6464","ning",PY_mb_ex_ning}, 
				{"6664","nong",PY_mb_ex_nong}, 
				{"6826","nuan",PY_mb_ex_nuan}, 
				{"7264","pang",PY_mb_ex_pang}, 
				{"7364","peng",PY_mb_ex_peng}, 
				{"7264","rang",PY_mb_ex_rang}, 
				{"7264","sang",PY_mb_ex_sang}, 
				{"7364","seng",PY_mb_ex_seng}, 
				{"7364","reng",PY_mb_ex_reng}, 
				{"7424","shai",PY_mb_ex_shai}, 
				{"7426","shan",PY_mb_ex_shan}, 
				{"7426","shao",PY_mb_ex_shao}, 
				{"7426","pian",PY_mb_ex_pian}, 
				{"7426","piao",PY_mb_ex_piao}, 
				{"7426","qian",PY_mb_ex_qian}, 
				{"7426","qiao",PY_mb_ex_qiao}, 
				{"7436","shen",PY_mb_ex_shen}, 
				{"7464","ping",PY_mb_ex_ping}, 
				{"7464","qing",PY_mb_ex_qing}, 
				{"7466","qion",PY_mb_ex_qiong}, 
				{"7468","shou",PY_mb_ex_shou}, 
				{"7482","shua",PY_mb_ex_shua}, 
				{"7484","shui",PY_mb_ex_shui}, 
				{"7486","shun",PY_mb_ex_shun}, 
				{"7486","shuo",PY_mb_ex_shuo}, 
				{"7664","rong",PY_mb_ex_rong}, 
				{"7664","song",PY_mb_ex_song},
				{"7826","suan",PY_mb_ex_suan}, 
				{"7826","quan",PY_mb_ex_quan}, 
				{"7826","ruan",PY_mb_ex_ruan}, 
				{"8264","tang",PY_mb_ex_tang}, 
				{"8364","teng",PY_mb_ex_teng}, 
				{"8426","tian",PY_mb_ex_tian}, 
				{"8426","tiao",PY_mb_ex_tiao}, 
				{"8464","ting",PY_mb_ex_ting}, 
				{"8664","tong",PY_mb_ex_tong}, 
				{"8826","tuan",PY_mb_ex_tuan}, 
				{"9264","wang",PY_mb_ex_wang}, 
				{"9264","zang",PY_mb_ex_zang}, 
				{"9264","yang",PY_mb_ex_yang}, 
				{"9364","weng",PY_mb_ex_weng}, 
				{"9364","zeng",PY_mb_ex_zeng}, 
				{"9424","zhai",PY_mb_ex_zhai}, 
				{"9426","zhan",PY_mb_ex_zhan}, 
				{"9426","zhao",PY_mb_ex_zhao}, 
				{"9426","xian",PY_mb_ex_xian}, 
				{"9426","xiao",PY_mb_ex_xiao}, 
				{"9436","zhen",PY_mb_ex_zhen}, 
				{"9464","xing",PY_mb_ex_xing}, 
				{"9464","ying",PY_mb_ex_ying}, 
				{"9466","zhon",PY_mb_ex_zhong}, 
				{"9468","zhou",PY_mb_ex_zhou}, 
				{"9482","zhua",PY_mb_ex_zhua}, 
				{"9484","zhui",PY_mb_ex_zhui}, 
				{"9486","zhun",PY_mb_ex_zhun}, 
				{"9486","zhuo",PY_mb_ex_zhuo}, 
				{"9466","xion",PY_mb_ex_xiong}, 
				{"9664","yong",PY_mb_ex_yong}, 
				{"9664","zong",PY_mb_ex_zong}, 
				{"9826","yuan",PY_mb_ex_yuan}, 
				{"9826","xuan",PY_mb_ex_xuan}, 
				{"9826","zuan",PY_mb_ex_zuan}, 
				{"94264","xiang",PY_mb_ex_xiang}, 
				{"94264","zhang",PY_mb_ex_zhang}, 
				{"94364","zheng",PY_mb_ex_zheng}, 
				{"94664","xiong",PY_mb_ex_xiong}, 
				{"94664","zhong",PY_mb_ex_zhong}, 
				{"94824","zhuai",PY_mb_ex_zhuai}, 
				{"94826","zhuan",PY_mb_ex_zhuan},				
				{"24264","chang",PY_mb_ex_chang},				
				{"24364","cheng",PY_mb_ex_cheng},
				{"24664","chong",PY_mb_ex_chong},
				{"24824","chuai",PY_mb_ex_chuai},
				{"24826","chuan",PY_mb_ex_chuan},
				{"48264","guang",PY_mb_ex_guang}, 
				{"48264","huang",PY_mb_ex_huang}, 
				{"54264","jiang",PY_mb_ex_jiang}, 
				{"54264","liang",PY_mb_ex_liang}, 
				{"54664","jiong",PY_mb_ex_jiong}, 
				{"58264","kuang",PY_mb_ex_kuang}, 
				{"64264","niang",PY_mb_ex_niang}, 
				{"74264","qiang",PY_mb_ex_qiang}, 
				{"74264","shang",PY_mb_ex_shang}, 
				{"74364","sheng",PY_mb_ex_sheng}, 
				{"74664","qiong",PY_mb_ex_qiong}, 
				{"74824","shuai",PY_mb_ex_shuai}, 
				{"74826","shuan",PY_mb_ex_shuan}, 
				{"248264","chuang",PY_mb_ex_chuang},
				{"748264","shuang",PY_mb_ex_shuang}, 
				{"948264","zhuang",PY_mb_ex_zhuang}, 
				{"","",PY_mb_ex_space} 
};
#endif 


