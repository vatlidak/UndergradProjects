ASKISI-3 14/1/2007/ PROGRAMMATISMOS SUSTIMATOS

ATLIDAKIS VAGGELIS        1115 2005 00010
AGGELOGIANNOPOULOS ARIS   1115 2005 00004


perigrafi programmatos myserver.c

sunartiseis:

1)void clean_up_child_process (int);
2)void timeToStop();
3)int read_from_client (int,struct hostent* );
4)main();


--main()

arxika uparxoun oi metavlites pou xrisimopouountai apo tis sunartiseis,oi opoies einai dilwmenes e3w apo 
tin  main wste na tis vlepoun oles oi sunartiseis kai na mporoun oi handler na kleinoun tous file 
descripitors twn diergasiwn oi opoies eite termatizoun oles mazi,eite mia(timeToStop-end).

arxika ginetai elegxos twn orismatwn,oson afora to pliqos alla kai tis times tous.
katopin i kuria diergasia dimiourgei to swlina epikoinwnias patera paidiwn kai kanei 
oles tis aparaitites energeies prokeimenou o peteras na akouei tcp sundeseis,epipleon 
xrisimopoieitai i setsockopt() i opoia parexei ti dunatotita grigoris epanaxrisimopoihshs twn port.
sti sunexeia i kuria diergasia genaei NUMCHILDREN paidia,kai o pateras ektelei diaforetiko kwdika apo ta 
paidia.

sugkekrimena gia ta paidia: 
arxika ta paidia mplokaroun to sigpipe,kai egkaQistoun handler gia to sigusr1 kai
diavazoun apo to swlina pou grafei o pateras,oloklirw to mnm to opoio autos grafei.
sti sunexeia,epeidi to mnm pou grafei o peteras exei sugkekrimeno format to paidi 3exwrizei tis 
aparaitites
plirofories gia ton pelati,tou opoiou i entoli akolouQei(proigeitai onoma,dgr_port).
sti sunexeia kanei tis aparaitites energies gia mia UDP sundesi me ton pelati kai
alegxei an o pelatis esteile end h timeToStop opote stelnei ta katalila simata,alliws ektelei me popen 
tin entoli UNIX. 
afou exei ektelesei tin entoli diavazei apo to arxeio,deikti sto opoio epistrefei i popen kai stelnei 
osa paketa megeQous 512 bytes apaitountai.
prin tin enar3i apostolis twn paketwn me to apotelesma tis entolisto paidi stelnei ena paketo 
me ta stoixeia: PID:COMMAND:RESULTS kai meta tin oloklirwsi tis apostolis paketwn apotelesmatwn stelnei 
mia frasi ston pelati gia na ton enimerwsi gia tin oloklirwsi apostolis apotelesmatwn tis trexousas 
entolis.
fusika ola ta proanaferQenta paketa mporoun na xaQoun me probFAIL.

gia ton patera:
arxika mplokarei to SIGPIPE kai egkaQista tous antistouxous handlers gai ta SIGUSR 1,2.
skopos tou patera einai na parakolouQei ena sunolo apo perigrafites pot Qa alla3oun katastasi(mesw tis select).
sugkekrimena o pateras akouei gia tcp sundeseis,an o perigrafitis pou allazei katastasi einai
i socket stin opoia o pateras akouei(passive com. endpoind) tote exoume aitisi gia nea TCP sundesei,
opote o pateras anoigei mia kainourgia sundesi kai prosQetei twn perigrafiti sto sunolo pou parakolouQei.
an o perigrafitis pou allazei katastasei den einai i Qura pou o pateras akou gia TCP sundeseis,alla 
aneikei sto set,
tote kapoios pelatis exei pliroforia diaQesimi gia diavasma,opote kaleitai i read_from_client().
an  read_from_client()<0 tote o pelatis exei aposundeQei opote apodesmeuontai oi aparaititoi poroi!




--read_from_client()
  kaleitai me orisma ena perigrafiti arxeiou kai to onoma tou pelati pou einai sundedemenos se auto o  
  socket.diavazei apo to sockets me orisma to opoio kliQike,kai sugkekrimena diavazei 256 bytes.
  a)an i read diavasei 0 bytes simainei oti o peletis aposundeQike kai i sunartisi epistrefei arnitiki 
    timi, prokeimenou na enimerwQei o pateras kai na apodesmeusei tous antistoixous porous.
  b)an i timi epistrofia tis read einai Qetiki tote arxika elegxei o peteras kai agnoei tis entoles 
    megaluteres apo 256 bytes.katopin zitaei apo ton pelati ton ariQmo tis Quras stin opoia akouei UDP sundesis
    telos afou etoimasei to paketo me ta katallila stoixeia(entoli,onoma,port) to grafei sto swlina
    kai epistrefei 0>-1.
  

--void timeToStop()
  einai o handler gia to SIGUSR1.
  elegxei an i diergasia pou pianei to sima einai paidi-i pateras kai prattei analoga.
  o pateras stelnei se ola ta paidia SIGUSR1 ,perimenei ola ta paidia na termatisoun kai
  mono tote kleinei tous perigrafites tou kai termatizei.
  ta paidia kleinountous perigrafites tous kai termatizoun.
  

--void clean_up_child_process()
  einai o handler gia to SIGUSR2.
  ta paidia stelnoun ston patera SIGUSR2 otan diavasoun end,kai autos perimenei na termatisou 
  etsi den dimiourgountai zobie processes (<defunct>).
  

*)paratiriseis:
 -oles oi sunartiseis pou mporei na diakopoun apo sima elegxontai gi auto kai epanekkinountai!
 -o sugxronismos ton paidiwn petuxainetai se polu kalo vaQmo kati to opoio fainetai kai apo ta apotelesmata
  tou server otan termatizei,opou ektupwntai poses entoles exei ektelesei kaQe paidi kai oi diafores den 
  einai megales.(ektos an prokeitai gia polu mikres entoles).
  fusika an ena paidi ektelei idi mia entoli den Qa diavasei apo ton swlina pou o pateras grafei mia 
  kainourgia entoli.
  me ta parapanw kaQistatai safes oti to diavasma twn paidiwn lamvanei up'opsin kai to forto ergasias tou kaQe paidiou.
 -o pateras elegxei tis entoles kai an einai megaluteri apo 256 bytes tis agnwei enimerwnontas ton pelati.
  epipleon uloipoieitai o stoixeiwdis elegxos swlinwsewn kai sunQetwn entolwn,opws autos perigrafetai stin ekfwnisi!
 

----------------------------------------------------------------------------------------------------------------------
B)perigrafi tou programmatos myclient.c


sunartiseis:
1)void myhandler()--handler--
2)void sigpipehandler()--handler--
3)main(int argc, char *argv[])


--main()
 kat'arxas kanei elegxo orismatwn,katopin kanei tis aparetites energeies gia 
 tin apokatastasi mias TCP sundesis stin port pou o server "akouei"(orisma).
 opws kai sto server,etsi kai edw ginetai xrisi tis setsockopt.
 epipleon ginetai oi aparaitites energies gia mia UDP epikoinwnia stin port pou o pelatis 
 exei parei ws orisma.
 o pelatis perimenei eisodo apo to xristi,i anamoni gia auto orizete isi me 5000 sec
 i anaktisi tis entolis ginete me tin fgets kai apo to telos tis entolis afaireitai o xar/ras 
 allagis grammis.
 o peletis stelnei ston e3upiretiti tin entoli mesw TCP sundeseis kai perimenei mexri na tou zitiQei
 i DGR_PORT stin opoia o pelatis akous UDP sundeseis,otan tou zitiQei tin stelnei.
 se auto to simei elegxetai an o xristis exei dwsei entoli timeToStop opote o client termatizei,afou
 apeleuQerwsei tous porous pou wfeilei.
 Epipleon ginetai elegxos an o pateras-server exei enimerwsei ton pelati gia tin apostoli mi egkuris 
 entolis,opote o pelatis sunexizei me alli entoli,xwris na anamenei apantisi.

na diekrinistei oti orizontai ta e3is timeout:
.) 5000 sec anamoni gia ton xristi.
.) 25 sec gia anapokrisi tou server,diladi toso megisto xrono exei o server gia na ektelesei mia entoli.
.) 0.8 xrono meta3u 2 paketwn,an perasei autos o xronos tote sunexizei me alli entoli,giati mallon ta 
   ta upoloipa paketa xaQikan.

paratiriseis:
.)gia tous handler simeiwnetai oti otan piastei sima sigpipe to programma termatizei kaQws den einai pia 
  sundedemenos o server,kai otan piastei sigalarm tote mallon o pelatis prepei na sunexisei me nea entoli
  kaQws exei xtupisei kapoio timeout!
.)to programma diavazei kai me anakateuQunsi Qewrwntas oti kaQe grammi periexei mia entoli,kai sto telos 
  uparxei TimeToStop gia na termatisei o pelatis.episis oi entoles me "//" stin arxi tous,agnoountai,kaQws
  Qewrountai sxolia.
.)Qa ginei mia perigrafi sxetika me tin probFail kai tin sumperifora tou pelati,sugkekrimena Qa dwQoun
  kapoia senaria ta opoia sxetizontai me ta xamena paketa kai tin sumperifora tou pelati(xronos anamonis ktl..)
  kai anadiknioun to pws e3artatai i poioita tis epikoinwnias apo tin probFAIL.
.)oles oi sunartiseis pou mporei na diakopoun apo sima elegxontai gi auto kai epanekkinountai!


Telos exoume ta e3is(me fQinousa ta3inomisi oson afora tin poiotita epikonwnias):

1)an exw probFail=0.0 kai Qewritika kanena paketo den xaQei,tote afou o pelatis lavei tin eidipoihsh oti
  teliwse i apostoli paketwn gia tin trexousa entoli,tote mporei amesa na sunexisei me alli entoli.se auti 
  tin periptesi exw ti veltistei taxutita stin epikoinwnia,kati to opoio diapistwnetai me anakateuqunsi 
  arxeiou pollwn entolwn.

2)an exw probFail>0.0 kai paei estw ena paketo apo tin entoli,alla xaQei i frasi telous,tote o pelatis 
  perimenei molis 0.5 sec afou toso orizetai to time-out meta3u twn diadoxikwn paketwn.diladi 0.5 sec meta 
  apo to teleutaio paketo,an den tou exei stalei allo,Qewrei oti ta upoloipa xaQikan kai sunexizei me nea
  entoli.

3)an xaQei to paketo me ta stoixeia PID:COMMAND:RESULT kai to apotelesma tis entolis xwraei se ena paketo 
  to opoio upoQetika xanetai.tote o pelatis den kaQusterei kaQolou dioti lamvanei ti frasi telous.

4)an ta apotelesmat einai kai pali ena paketo to opoio xanetai,opws kai i frasi telous,alla aposteletai 
  to arxiko paketo me ta stoixeia PID:COMMAD:RESULTS tote o pelatis perimenei 0.5 sec afou toso orizetai to 
  time-out meta3u diadoxikwn paketwn.

5)an xaQoun ola ta paketa tote o pelatis perinei 25 sec afou toso orizetai o xronos anamonis gia to 
  server.simeiwnetai oti orizetai toso giati an den dwQei mikroteri timi tote Qa uparxei problima me 
  entoles pou kaQusteroun na ektelestoun.p.x.: ls -alr /usr/ | wc apaitei peripou 10 sec...an oristei 
  xronos anamonis< 215 sec tote i entoli den Qa ekteleitai.

6)Telos an grapsw entoli ston pelati kai o server exei aposundeQei tote o pelatis pairnei SIGPIPE kai 
  amesws termatizei afou apeleuqerwsei tous porous tou.
  
-------------------------------------------------------------------------------------------------------------



