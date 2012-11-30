/* Automatically generated file with GNU Octave */

/* File name: "TimeSyncFilter.octave" */
/* Filter taps in time-domain */

#include "TimeSyncFilter.h"

/*********************************************************/
/* Filter taps for 24000  Hz sample rate                 */
/* Low pass prototype for Hilbert-filter 5 kHz bandwidth */
const float fHilLPProt5_24[NUM_TAPS_HILB_FILT_5_24] =
{
	-0.00569076550675578878f,
	-0.02636034308612325572f,
	-0.02937823007744868112f,
	-0.03641852325814370211f,
	-0.03142942181939990809f,
	-0.01637537410250772263f,
	0.00656747636438384432f,
	0.02973961497116888592f,
	0.04354267422415943056f,
	0.03979947985889148443f,
	0.01591873397251728633f,
	-0.02252779213687858273f,
	-0.06193643121947790126f,
	-0.08415439076086959902f,
	-0.07240212520555380782f,
	-0.01778818567713004797f,
	0.07614474571814264237f,
	0.19276479774695770564f,
	0.30614513453813779753f,
	0.38848815850845630493f,
	0.41858314139975233426f,
	0.38848815850845630493f,
	0.30614513453813779753f,
	0.19276479774695770564f,
	0.07614474571814264237f,
	-0.01778818567713004797f,
	-0.07240212520555380782f,
	-0.08415439076086959902f,
	-0.06193643121947790126f,
	-0.02252779213687858273f,
	0.01591873397251728633f,
	0.03979947985889148443f,
	0.04354267422415943056f,
	0.02973961497116888592f,
	0.00656747636438384432f,
	-0.01637537410250772263f,
	-0.03142942181939990809f,
	-0.03641852325814370211f,
	-0.02937823007744868112f,
	-0.02636034308612325572f,
	-0.00569076550675578878f
};
/* Low pass prototype for Hilbert-filter 10 kHz bandwidth */
const float fHilLPProt10_24[NUM_TAPS_HILB_FILT_10_24] =
{
	-0.01126468176123466419f,
	-0.04573315426073081696f,
	-0.04613359715612273815f,
	-0.01553969363799070913f,
	0.02609020026415660373f,
	0.02581015289726837705f,
	-0.01557387400464138594f,
	-0.03833506043935425850f,
	-0.00187687942508038010f,
	0.04667501349941612782f,
	0.02908420049591232265f,
	-0.04322475920237642266f,
	-0.06357648622222950019f,
	0.02023288609187070403f,
	0.10061090960274908512f,
	0.03349542543589328208f,
	-0.13368194912443889799f,
	-0.14938345486248272298f,
	0.15656820555030517839f,
	0.61449202657603041455f,
	0.83521780153904756627f,
	0.61449202657603041455f,
	0.15656820555030517839f,
	-0.14938345486248272298f,
	-0.13368194912443889799f,
	0.03349542543589328208f,
	0.10061090960274908512f,
	0.02023288609187070403f,
	-0.06357648622222950019f,
	-0.04322475920237642266f,
	0.02908420049591232265f,
	0.04667501349941612782f,
	-0.00187687942508038010f,
	-0.03833506043935425850f,
	-0.01557387400464138594f,
	0.02581015289726837705f,
	0.02609020026415660373f,
	-0.01553969363799070913f,
	-0.04613359715612273815f,
	-0.04573315426073081696f,
	-0.01126468176123466419f
};

/*********************************************************/
/* Filter taps for 48000  Hz sample rate                 */
/* Low pass prototype for Hilbert-filter 5 kHz bandwidth */
const float fHilLPProt5_48[NUM_TAPS_HILB_FILT_5_48] =
{
	-0.00023478690135598997f,
	-0.01413273123257565052f,
	-0.01017230192682962338f,
	-0.01304125403484751242f,
	-0.01544581885437787058f,
	-0.01719189314304302857f,
	-0.01797805913050802562f,
	-0.01756078453316530993f,
	-0.01578934312697760980f,
	-0.01263195529532759077f,
	-0.00820332123308755920f,
	-0.00277338729221826260f,
	0.00324427314311573388f,
	0.00931850748247521794f,
	0.01484033371446751709f,
	0.01918022356749162285f,
	0.02175595657975005690f,
	0.02209542479897394149f,
	0.01990530294260488622f,
	0.01513474285260030250f,
	0.00797330862076401498f,
	-0.00105904536850926693f,
	-0.01125337053287578555f,
	-0.02158415494814015095f,
	-0.03095323089368840971f,
	-0.03817105049025057428f,
	-0.04207091334282069689f,
	-0.04166127154048478859f,
	-0.03620461906153087106f,
	-0.02528991674297844522f,
	-0.00890929852171523304f,
	0.01249919843339511449f,
	0.03806462188251723971f,
	0.06653898928215996877f,
	0.09637633415758371791f,
	0.12583010282143200498f,
	0.15308215964179835988f,
	0.17639986973775698131f,
	0.19426476716070920081f,
	0.20548251442781911846f,
	0.20931404028183486776f,
	0.20548251442781911846f,
	0.19426476716070920081f,
	0.17639986973775698131f,
	0.15308215964179835988f,
	0.12583010282143200498f,
	0.09637633415758371791f,
	0.06653898928215996877f,
	0.03806462188251723971f,
	0.01249919843339511449f,
	-0.00890929852171523304f,
	-0.02528991674297844522f,
	-0.03620461906153087106f,
	-0.04166127154048478859f,
	-0.04207091334282069689f,
	-0.03817105049025057428f,
	-0.03095323089368840971f,
	-0.02158415494814015095f,
	-0.01125337053287578555f,
	-0.00105904536850926693f,
	0.00797330862076401498f,
	0.01513474285260030250f,
	0.01990530294260488622f,
	0.02209542479897394149f,
	0.02175595657975005690f,
	0.01918022356749162285f,
	0.01484033371446751709f,
	0.00931850748247521794f,
	0.00324427314311573388f,
	-0.00277338729221826260f,
	-0.00820332123308755920f,
	-0.01263195529532759077f,
	-0.01578934312697760980f,
	-0.01756078453316530993f,
	-0.01797805913050802562f,
	-0.01719189314304302857f,
	-0.01544581885437787058f,
	-0.01304125403484751242f,
	-0.01017230192682962338f,
	-0.01413273123257565052f,
	-0.00023478690135598997f
};
/* Low pass prototype for Hilbert-filter 10 kHz bandwidth */
const float fHilLPProt10_48[NUM_TAPS_HILB_FILT_10_48] =
{
	-0.00265802839641611326f,
	-0.01970912920536988661f,
	-0.01968785016839483606f,
	-0.02461003801677347572f,
	-0.02377152869170011396f,
	-0.01784125782630162013f,
	-0.00774741064843881451f,
	0.00367011282222752706f,
	0.01274005286505880061f,
	0.01627980915842414458f,
	0.01287464243669448477f,
	0.00369846447256556073f,
	-0.00773496518628763365f,
	-0.01669723654801230639f,
	-0.01911669051862374333f,
	-0.01331282246842796328f,
	-0.00096141840730783396f,
	0.01324303685995057052f,
	0.02329220468584962053f,
	0.02423221662315279759f,
	0.01451613102673328902f,
	-0.00299343593023826664f,
	-0.02163090369786577205f,
	-0.03329909879823830104f,
	-0.03181434789619437542f,
	-0.01576875824581750601f,
	0.01010047032122583788f,
	0.03597569824192357879f,
	0.05032854697617934747f,
	0.04449817137639855424f,
	0.01680392433297665106f,
	-0.02538219901248268615f,
	-0.06680857669836365309f,
	-0.08865984466169557487f,
	-0.07471364357013575430f,
	-0.01742631653997888871f,
	0.07826912309879234531f,
	0.19502785542440378985f,
	0.30725842758206578509f,
	0.38818628285609518835f,
	0.41765160751489427415f,
	0.38818628285609518835f,
	0.30725842758206578509f,
	0.19502785542440378985f,
	0.07826912309879234531f,
	-0.01742631653997888871f,
	-0.07471364357013575430f,
	-0.08865984466169557487f,
	-0.06680857669836365309f,
	-0.02538219901248268615f,
	0.01680392433297665106f,
	0.04449817137639855424f,
	0.05032854697617934747f,
	0.03597569824192357879f,
	0.01010047032122583788f,
	-0.01576875824581750601f,
	-0.03181434789619437542f,
	-0.03329909879823830104f,
	-0.02163090369786577205f,
	-0.00299343593023826664f,
	0.01451613102673328902f,
	0.02423221662315279759f,
	0.02329220468584962053f,
	0.01324303685995057052f,
	-0.00096141840730783396f,
	-0.01331282246842796328f,
	-0.01911669051862374333f,
	-0.01669723654801230639f,
	-0.00773496518628763365f,
	0.00369846447256556073f,
	0.01287464243669448477f,
	0.01627980915842414458f,
	0.01274005286505880061f,
	0.00367011282222752706f,
	-0.00774741064843881451f,
	-0.01784125782630162013f,
	-0.02377152869170011396f,
	-0.02461003801677347572f,
	-0.01968785016839483606f,
	-0.01970912920536988661f,
	-0.00265802839641611326f
};

/*********************************************************/
/* Filter taps for 96000  Hz sample rate                 */
/* Low pass prototype for Hilbert-filter 5 kHz bandwidth */
const float fHilLPProt5_96[NUM_TAPS_HILB_FILT_5_96] =
{
	0.00344351743508067992f,
	-0.00925278666089145857f,
	-0.00558109728270497502f,
	-0.00498383511661063070f,
	-0.00530616061348714637f,
	-0.00589380395789674150f,
	-0.00653740121416073947f,
	-0.00716012279958981937f,
	-0.00772818463844002386f,
	-0.00821644219268250972f,
	-0.00860230665526456884f,
	-0.00886688902704232430f,
	-0.00899540061654360498f,
	-0.00897227872550473808f,
	-0.00878597216042170497f,
	-0.00843074145195851256f,
	-0.00789965729010909737f,
	-0.00719488211216580496f,
	-0.00632160033775589544f,
	-0.00528664203201396031f,
	-0.00410869213098709503f,
	-0.00280248379868558700f,
	-0.00139512179550311546f,
	0.00008747448821593897f,
	0.00161278575662688077f,
	0.00314605623551871992f,
	0.00465007183578734773f,
	0.00608512786830577718f,
	0.00741268230471877742f,
	0.00859111053614111490f,
	0.00958475270348160477f,
	0.01035579051182581450f,
	0.01087317510357018596f,
	0.01111014418734333417f,
	0.01104327872205521088f,
	0.01065959640958474147f,
	0.00995009586244724117f,
	0.00891503980096722444f,
	0.00756416805828884035f,
	0.00591344210890162522f,
	0.00398985845533233151f,
	0.00182793215546468257f,
	-0.00052911899276757732f,
	-0.00303075094175071650f,
	-0.00561841432050232473f,
	-0.00822564602769767020f,
	-0.01079169464381161958f,
	-0.01322346999139634161f,
	-0.01547919515286888537f,
	-0.01743980734542945749f,
	-0.01907502030420905881f,
	-0.02029786951388848348f,
	-0.02102552484619302567f,
	-0.02121826214378224815f,
	-0.02082868326392792874f,
	-0.01980172006189571260f,
	-0.01809945171760379834f,
	-0.01570989061424140493f,
	-0.01263436893043458874f,
	-0.00887693353222442950f,
	-0.00445021061926967592f,
	0.00061044296575558574f,
	0.00625203789673288782f,
	0.01241960164038924744f,
	0.01903740358187556297f,
	0.02601834651971359283f,
	0.03327718710200216340f,
	0.04070199593795786885f,
	0.04819495035104086333f,
	0.05563743473218094038f,
	0.06291924609621986353f,
	0.06992544587146180823f,
	0.07654474645721114079f,
	0.08267062871755088971f,
	0.08820267891354671708f,
	0.09305050403474991738f,
	0.09713211588782331984f,
	0.10038100887603268463f,
	0.10274120037334986966f,
	0.10417324993660337373f,
	0.10465392914788113066f,
	0.10417324993660337373f,
	0.10274120037334986966f,
	0.10038100887603268463f,
	0.09713211588782331984f,
	0.09305050403474991738f,
	0.08820267891354671708f,
	0.08267062871755088971f,
	0.07654474645721114079f,
	0.06992544587146180823f,
	0.06291924609621986353f,
	0.05563743473218094038f,
	0.04819495035104086333f,
	0.04070199593795786885f,
	0.03327718710200216340f,
	0.02601834651971359283f,
	0.01903740358187556297f,
	0.01241960164038924744f,
	0.00625203789673288782f,
	0.00061044296575558574f,
	-0.00445021061926967592f,
	-0.00887693353222442950f,
	-0.01263436893043458874f,
	-0.01570989061424140493f,
	-0.01809945171760379834f,
	-0.01980172006189571260f,
	-0.02082868326392792874f,
	-0.02121826214378224815f,
	-0.02102552484619302567f,
	-0.02029786951388848348f,
	-0.01907502030420905881f,
	-0.01743980734542945749f,
	-0.01547919515286888537f,
	-0.01322346999139634161f,
	-0.01079169464381161958f,
	-0.00822564602769767020f,
	-0.00561841432050232473f,
	-0.00303075094175071650f,
	-0.00052911899276757732f,
	0.00182793215546468257f,
	0.00398985845533233151f,
	0.00591344210890162522f,
	0.00756416805828884035f,
	0.00891503980096722444f,
	0.00995009586244724117f,
	0.01065959640958474147f,
	0.01104327872205521088f,
	0.01111014418734333417f,
	0.01087317510357018596f,
	0.01035579051182581450f,
	0.00958475270348160477f,
	0.00859111053614111490f,
	0.00741268230471877742f,
	0.00608512786830577718f,
	0.00465007183578734773f,
	0.00314605623551871992f,
	0.00161278575662688077f,
	0.00008747448821593897f,
	-0.00139512179550311546f,
	-0.00280248379868558700f,
	-0.00410869213098709503f,
	-0.00528664203201396031f,
	-0.00632160033775589544f,
	-0.00719488211216580496f,
	-0.00789965729010909737f,
	-0.00843074145195851256f,
	-0.00878597216042170497f,
	-0.00897227872550473808f,
	-0.00899540061654360498f,
	-0.00886688902704232430f,
	-0.00860230665526456884f,
	-0.00821644219268250972f,
	-0.00772818463844002386f,
	-0.00716012279958981937f,
	-0.00653740121416073947f,
	-0.00589380395789674150f,
	-0.00530616061348714637f,
	-0.00498383511661063070f,
	-0.00558109728270497502f,
	-0.00925278666089145857f,
	0.00344351743508067992f
};
/* Low pass prototype for Hilbert-filter 10 kHz bandwidth */
const float fHilLPProt10_96[NUM_TAPS_HILB_FILT_10_96] =
{
	0.00180344649481576583f,
	-0.01124009964748978740f,
	-0.00785180164589377276f,
	-0.00884350989474976153f,
	-0.01028733430513804198f,
	-0.01148777489956089547f,
	-0.01222768511822151793f,
	-0.01238419018663358337f,
	-0.01188721348203487793f,
	-0.01071671218323581691f,
	-0.00891561823654698354f,
	-0.00658141217982661977f,
	-0.00387388218022571536f,
	-0.00099159837611916988f,
	0.00183148048587972396f,
	0.00436046667012210572f,
	0.00636773988945150450f,
	0.00767020063474555154f,
	0.00813549924077096830f,
	0.00771363789065680934f,
	0.00643161268168638677f,
	0.00440984331326294346f,
	0.00183926016085020263f,
	-0.00101921787324760833f,
	-0.00387312271889942708f,
	-0.00641128204167752940f,
	-0.00835040137490942851f,
	-0.00945023523258861804f,
	-0.00955626209918723768f,
	-0.00860472925315072280f,
	-0.00664986594676022190f,
	-0.00384917751000241016f,
	-0.00046802134898949089f,
	0.00315847516488977501f,
	0.00664233703344021056f,
	0.00959721677185411924f,
	0.01166459232275667696f,
	0.01256894798133510738f,
	0.01213665471651462734f,
	0.01033570904691685950f,
	0.00727276647519238019f,
	0.00320535615645141901f,
	-0.00149043733971136521f,
	-0.00633774501219406660f,
	-0.01081748392026036024f,
	-0.01440857752172155018f,
	-0.01665785223749342153f,
	-0.01722101911137990243f,
	-0.01591551049593805528f,
	-0.01274020895431540561f,
	-0.00789464447183665582f,
	-0.00177933573388649384f,
	0.00505288848871142220f,
	0.01187125707115641721f,
	0.01797611401443159618f,
	0.02262289577982389693f,
	0.02515979829824038783f,
	0.02511152213473104994f,
	0.02223827238607434947f,
	0.01655931469413613258f,
	0.00839313046551252474f,
	-0.00164946085265967632f,
	-0.01270073469585174079f,
	-0.02368630919438210677f,
	-0.03341811447416495606f,
	-0.04067946659513506369f,
	-0.04434272493341542831f,
	-0.04345906680067209565f,
	-0.03736737079420434510f,
	-0.02575534941281795720f,
	-0.00872377146808960870f,
	0.01321211127230192094f,
	0.03912482345070567719f,
	0.06774190956764471194f,
	0.09751232355549017961f,
	0.12672924756866854601f,
	0.15363758773824201520f,
	0.17657978111138783461f,
	0.19410510228858693371f,
	0.20509623004857788220f,
	0.20883953705554986202f,
	0.20509623004857788220f,
	0.19410510228858693371f,
	0.17657978111138783461f,
	0.15363758773824201520f,
	0.12672924756866854601f,
	0.09751232355549017961f,
	0.06774190956764471194f,
	0.03912482345070567719f,
	0.01321211127230192094f,
	-0.00872377146808960870f,
	-0.02575534941281795720f,
	-0.03736737079420434510f,
	-0.04345906680067209565f,
	-0.04434272493341542831f,
	-0.04067946659513506369f,
	-0.03341811447416495606f,
	-0.02368630919438210677f,
	-0.01270073469585174079f,
	-0.00164946085265967632f,
	0.00839313046551252474f,
	0.01655931469413613258f,
	0.02223827238607434947f,
	0.02511152213473104994f,
	0.02515979829824038783f,
	0.02262289577982389693f,
	0.01797611401443159618f,
	0.01187125707115641721f,
	0.00505288848871142220f,
	-0.00177933573388649384f,
	-0.00789464447183665582f,
	-0.01274020895431540561f,
	-0.01591551049593805528f,
	-0.01722101911137990243f,
	-0.01665785223749342153f,
	-0.01440857752172155018f,
	-0.01081748392026036024f,
	-0.00633774501219406660f,
	-0.00149043733971136521f,
	0.00320535615645141901f,
	0.00727276647519238019f,
	0.01033570904691685950f,
	0.01213665471651462734f,
	0.01256894798133510738f,
	0.01166459232275667696f,
	0.00959721677185411924f,
	0.00664233703344021056f,
	0.00315847516488977501f,
	-0.00046802134898949089f,
	-0.00384917751000241016f,
	-0.00664986594676022190f,
	-0.00860472925315072280f,
	-0.00955626209918723768f,
	-0.00945023523258861804f,
	-0.00835040137490942851f,
	-0.00641128204167752940f,
	-0.00387312271889942708f,
	-0.00101921787324760833f,
	0.00183926016085020263f,
	0.00440984331326294346f,
	0.00643161268168638677f,
	0.00771363789065680934f,
	0.00813549924077096830f,
	0.00767020063474555154f,
	0.00636773988945150450f,
	0.00436046667012210572f,
	0.00183148048587972396f,
	-0.00099159837611916988f,
	-0.00387388218022571536f,
	-0.00658141217982661977f,
	-0.00891561823654698354f,
	-0.01071671218323581691f,
	-0.01188721348203487793f,
	-0.01238419018663358337f,
	-0.01222768511822151793f,
	-0.01148777489956089547f,
	-0.01028733430513804198f,
	-0.00884350989474976153f,
	-0.00785180164589377276f,
	-0.01124009964748978740f,
	0.00180344649481576583f
};

/*********************************************************/
/* Filter taps for 192000 Hz sample rate                 */
/* Low pass prototype for Hilbert-filter 5 kHz bandwidth */
const float fHilLPProt5_192[NUM_TAPS_HILB_FILT_5_192] =
{
	0.00597665458855372710f,
	-0.00599723610232585913f,
	-0.00416343322103561973f,
	-0.00319478044681177761f,
	-0.00272070988585160472f,
	-0.00252725052890332390f,
	-0.00249493960076497667f,
	-0.00255279542451024603f,
	-0.00266280490719596067f,
	-0.00280026677522371165f,
	-0.00295331808372476272f,
	-0.00311149921388329453f,
	-0.00327195281802817152f,
	-0.00342920389731763559f,
	-0.00358241260006355970f,
	-0.00372763273157487212f,
	-0.00386535795541761420f,
	-0.00399197699762842643f,
	-0.00410823806245130992f,
	-0.00421087047286859174f,
	-0.00430070137878533435f,
	-0.00437451099058642004f,
	-0.00443327554094821111f,
	-0.00447386441514230956f,
	-0.00449728337272876661f,
	-0.00450070368211401891f,
	-0.00448564072896682695f,
	-0.00444921806678572323f,
	-0.00439271773500476883f,
	-0.00431384550188177590f,
	-0.00421428458466598620f,
	-0.00409184050267586384f,
	-0.00394872831075239027f,
	-0.00378281526366694041f,
	-0.00359601691154874626f,
	-0.00338727595055194003f,
	-0.00315856702839396007f,
	-0.00290936781308935534f,
	-0.00263940303561229200f,
	-0.00235764094657127301f,
	-0.00204423320239259737f,
	-0.00173825112198132468f,
	-0.00139445145486153462f,
	-0.00104702690217608617f,
	-0.00069770138674771969f,
	-0.00032721789884580408f,
	0.00005236701905384986f,
	0.00043007648096523801f,
	0.00080807343972609980f,
	0.00119388155428848657f,
	0.00158069353399466314f,
	0.00196182652819726399f,
	0.00233152013013390507f,
	0.00269373314845258944f,
	0.00304723087536440829f,
	0.00339049017836712784f,
	0.00371578550914821804f,
	0.00402130255935067606f,
	0.00430302394510266063f,
	0.00456255579580323780f,
	0.00479699325636780746f,
	0.00500644585811273451f,
	0.00518538194486219822f,
	0.00533263760437352723f,
	0.00544383146434254672f,
	0.00551993939189697989f,
	0.00555808623765301994f,
	0.00556019487875531772f,
	0.00552354176505071275f,
	0.00544903791146523261f,
	0.00533366448301975191f,
	0.00517881838434557616f,
	0.00498138729158772824f,
	0.00474349293143737881f,
	0.00446390968685565683f,
	0.00414503189269505978f,
	0.00378663649845625621f,
	0.00339128098279980897f,
	0.00296023579944870979f,
	0.00249343980000371005f,
	0.00199865169224407949f,
	0.00146929120581353913f,
	0.00091684036591791200f,
	0.00033861699572947551f,
	-0.00026366982148544977f,
	-0.00087991749030925394f,
	-0.00151264685402978469f,
	-0.00215745215147775072f,
	-0.00280799389532635467f,
	-0.00345907864879364596f,
	-0.00411168788624220391f,
	-0.00475790066170503952f,
	-0.00539306941712722372f,
	-0.00601145661722567171f,
	-0.00661254616387156602f,
	-0.00718892749738260072f,
	-0.00773630647343808136f,
	-0.00824789278685386130f,
	-0.00872303389498829164f,
	-0.00915515823322218120f,
	-0.00954045154979463877f,
	-0.00987157831763238978f,
	-0.01014753270826629014f,
	-0.01036298711678708927f,
	-0.01051606467260652981f,
	-0.01060024897582311637f,
	-0.01061410790452165832f,
	-0.01055224242832967542f,
	-0.01041461382205480582f,
	-0.01019735985120746521f,
	-0.00990001981635641425f,
	-0.00951768192706760330f,
	-0.00905124412500357516f,
	-0.00849759223092428836f,
	-0.00785822661899312006f,
	-0.00713204406418306829f,
	-0.00632054581484522808f,
	-0.00542230064403374443f,
	-0.00443942385813975247f,
	-0.00337345328487710086f,
	-0.00222481131840870927f,
	-0.00099909395180869539f,
	0.00030396134647563160f,
	0.00168015042301020699f,
	0.00312416606168987787f,
	0.00463576576239191091f,
	0.00620736351057628484f,
	0.00783581464960832544f,
	0.00951564400838915067f,
	0.01124188397409009443f,
	0.01300602083372496588f,
	0.01480623060107431541f,
	0.01663417052205172150f,
	0.01848403207205377707f,
	0.02034723842943865837f,
	0.02222039538699616124f,
	0.02409392254298018191f,
	0.02596185922694409579f,
	0.02781502998710564528f,
	0.02964966269497559814f,
	0.03145620378068833545f,
	0.03322865303602406950f,
	0.03495783862948610710f,
	0.03664039316051079243f,
	0.03826754611338047812f,
	0.03983389666582597827f,
	0.04133050032717214967f,
	0.04275440827610720029f,
	0.04409754280452575503f,
	0.04535552957104477256f,
	0.04652115674557853742f,
	0.04759242302967703342f,
	0.04856225635402061647f,
	0.04942903342286031343f,
	0.05018744358183882537f,
	0.05083485939956271238f,
	0.05136716929486204175f,
	0.05178481263467971107f,
	0.05208395534618442957f,
	0.05226428128764680492f,
	0.05232514598159419134f,
	0.05226428128764680492f,
	0.05208395534618442957f,
	0.05178481263467971107f,
	0.05136716929486204175f,
	0.05083485939956271238f,
	0.05018744358183882537f,
	0.04942903342286031343f,
	0.04856225635402061647f,
	0.04759242302967703342f,
	0.04652115674557853742f,
	0.04535552957104477256f,
	0.04409754280452575503f,
	0.04275440827610720029f,
	0.04133050032717214967f,
	0.03983389666582597827f,
	0.03826754611338047812f,
	0.03664039316051079243f,
	0.03495783862948610710f,
	0.03322865303602406950f,
	0.03145620378068833545f,
	0.02964966269497559814f,
	0.02781502998710564528f,
	0.02596185922694409579f,
	0.02409392254298018191f,
	0.02222039538699616124f,
	0.02034723842943865837f,
	0.01848403207205377707f,
	0.01663417052205172150f,
	0.01480623060107431541f,
	0.01300602083372496588f,
	0.01124188397409009443f,
	0.00951564400838915067f,
	0.00783581464960832544f,
	0.00620736351057628484f,
	0.00463576576239191091f,
	0.00312416606168987787f,
	0.00168015042301020699f,
	0.00030396134647563160f,
	-0.00099909395180869539f,
	-0.00222481131840870927f,
	-0.00337345328487710086f,
	-0.00443942385813975247f,
	-0.00542230064403374443f,
	-0.00632054581484522808f,
	-0.00713204406418306829f,
	-0.00785822661899312006f,
	-0.00849759223092428836f,
	-0.00905124412500357516f,
	-0.00951768192706760330f,
	-0.00990001981635641425f,
	-0.01019735985120746521f,
	-0.01041461382205480582f,
	-0.01055224242832967542f,
	-0.01061410790452165832f,
	-0.01060024897582311637f,
	-0.01051606467260652981f,
	-0.01036298711678708927f,
	-0.01014753270826629014f,
	-0.00987157831763238978f,
	-0.00954045154979463877f,
	-0.00915515823322218120f,
	-0.00872303389498829164f,
	-0.00824789278685386130f,
	-0.00773630647343808136f,
	-0.00718892749738260072f,
	-0.00661254616387156602f,
	-0.00601145661722567171f,
	-0.00539306941712722372f,
	-0.00475790066170503952f,
	-0.00411168788624220391f,
	-0.00345907864879364596f,
	-0.00280799389532635467f,
	-0.00215745215147775072f,
	-0.00151264685402978469f,
	-0.00087991749030925394f,
	-0.00026366982148544977f,
	0.00033861699572947551f,
	0.00091684036591791200f,
	0.00146929120581353913f,
	0.00199865169224407949f,
	0.00249343980000371005f,
	0.00296023579944870979f,
	0.00339128098279980897f,
	0.00378663649845625621f,
	0.00414503189269505978f,
	0.00446390968685565683f,
	0.00474349293143737881f,
	0.00498138729158772824f,
	0.00517881838434557616f,
	0.00533366448301975191f,
	0.00544903791146523261f,
	0.00552354176505071275f,
	0.00556019487875531772f,
	0.00555808623765301994f,
	0.00551993939189697989f,
	0.00544383146434254672f,
	0.00533263760437352723f,
	0.00518538194486219822f,
	0.00500644585811273451f,
	0.00479699325636780746f,
	0.00456255579580323780f,
	0.00430302394510266063f,
	0.00402130255935067606f,
	0.00371578550914821804f,
	0.00339049017836712784f,
	0.00304723087536440829f,
	0.00269373314845258944f,
	0.00233152013013390507f,
	0.00196182652819726399f,
	0.00158069353399466314f,
	0.00119388155428848657f,
	0.00080807343972609980f,
	0.00043007648096523801f,
	0.00005236701905384986f,
	-0.00032721789884580408f,
	-0.00069770138674771969f,
	-0.00104702690217608617f,
	-0.00139445145486153462f,
	-0.00173825112198132468f,
	-0.00204423320239259737f,
	-0.00235764094657127301f,
	-0.00263940303561229200f,
	-0.00290936781308935534f,
	-0.00315856702839396007f,
	-0.00338727595055194003f,
	-0.00359601691154874626f,
	-0.00378281526366694041f,
	-0.00394872831075239027f,
	-0.00409184050267586384f,
	-0.00421428458466598620f,
	-0.00431384550188177590f,
	-0.00439271773500476883f,
	-0.00444921806678572323f,
	-0.00448564072896682695f,
	-0.00450070368211401891f,
	-0.00449728337272876661f,
	-0.00447386441514230956f,
	-0.00443327554094821111f,
	-0.00437451099058642004f,
	-0.00430070137878533435f,
	-0.00421087047286859174f,
	-0.00410823806245130992f,
	-0.00399197699762842643f,
	-0.00386535795541761420f,
	-0.00372763273157487212f,
	-0.00358241260006355970f,
	-0.00342920389731763559f,
	-0.00327195281802817152f,
	-0.00311149921388329453f,
	-0.00295331808372476272f,
	-0.00280026677522371165f,
	-0.00266280490719596067f,
	-0.00255279542451024603f,
	-0.00249493960076497667f,
	-0.00252725052890332390f,
	-0.00272070988585160472f,
	-0.00319478044681177761f,
	-0.00416343322103561973f,
	-0.00599723610232585913f,
	0.00597665458855372710f
};
/* Low pass prototype for Hilbert-filter 10 kHz bandwidth */
const float fHilLPProt10_192[NUM_TAPS_HILB_FILT_10_192] =
{
	0.00481248575344039864f,
	-0.00716589506396039279f,
	-0.00483104839579957986f,
	-0.00403755979436868848f,
	-0.00393264864177109499f,
	-0.00412680221289675464f,
	-0.00444439656728895256f,
	-0.00479880981760322841f,
	-0.00514931429740205643f,
	-0.00546873276816104391f,
	-0.00574392404076935672f,
	-0.00596090985719547033f,
	-0.00611333808201909232f,
	-0.00619165365774415524f,
	-0.00619289644595245100f,
	-0.00611053843221215278f,
	-0.00594549547642638301f,
	-0.00569416567973387092f,
	-0.00536137211353130989f,
	-0.00494766532957854541f,
	-0.00446125148038516942f,
	-0.00390610983098922931f,
	-0.00329489407437547456f,
	-0.00263461180060850422f,
	-0.00194091647741515818f,
	-0.00122335318914068266f,
	-0.00049995562645775021f,
	0.00021818695100586739f,
	0.00091254266260019923f,
	0.00157202114212711265f,
	0.00217778967729608756f,
	0.00272001967611711516f,
	0.00318247666178877358f,
	0.00355796635471669403f,
	0.00383316557616066467f,
	0.00400576663174091047f,
	0.00406637365429457585f,
	0.00401817237431850108f,
	0.00385570429810669748f,
	0.00358888716232179253f,
	0.00321672795267135842f,
	0.00275377271101419786f,
	0.00221027404170605042f,
	0.00158742964024669551f,
	0.00093190744973898807f,
	0.00021471061463893413f,
	-0.00050732442462352121f,
	-0.00122487278964805496f,
	-0.00193243295402609964f,
	-0.00260262036934346590f,
	-0.00320569595551410376f,
	-0.00373322525549582215f,
	-0.00417498981526077083f,
	-0.00451316127749329041f,
	-0.00473021224181881250f,
	-0.00481822304547491718f,
	-0.00477603064590864830f,
	-0.00460436972480312168f,
	-0.00430432720003204403f,
	-0.00387732569881268788f,
	-0.00333115203754065590f,
	-0.00267642848078327540f,
	-0.00192996538719237285f,
	-0.00111007440097362145f,
	-0.00023864494720773338f,
	0.00066372847437634077f,
	0.00157173086505566113f,
	0.00246339066993469082f,
	0.00331207464361695609f,
	0.00409565161990285784f,
	0.00478839895383255474f,
	0.00537108063511111764f,
	0.00582245751451044864f,
	0.00612867425751953149f,
	0.00627454051766952476f,
	0.00625350850557541971f,
	0.00605921348512520903f,
	0.00569384042514932756f,
	0.00515909698646572525f,
	0.00446732161081668782f,
	0.00362936703140398021f,
	0.00266663729095989281f,
	0.00159717493699539710f,
	0.00045062194073587094f,
	-0.00074750617334680490f,
	-0.00196511218381902834f,
	-0.00316754016881003273f,
	-0.00432832903504513661f,
	-0.00540449562766091938f,
	-0.00637312932050280567f,
	-0.00720134191300308719f,
	-0.00785828592041203956f,
	-0.00832421895024035990f,
	-0.00858027672747722209f,
	-0.00860745777599359815f,
	-0.00839848859438984373f,
	-0.00795332094774038427f,
	-0.00727268812042745731f,
	-0.00636440350479003814f,
	-0.00524630112104608731f,
	-0.00394178783419616569f,
	-0.00247683369968309565f,
	-0.00088465535224722567f,
	0.00079720365717879328f,
	0.00252502312089961578f,
	0.00425467564189114991f,
	0.00594060125538240467f,
	0.00753616908782961739f,
	0.00899261310973482192f,
	0.01026594777024173941f,
	0.01131180242891924835f,
	0.01209467034581716144f,
	0.01257958227088597052f,
	0.01274165590324968268f,
	0.01255830877472648849f,
	0.01201957192001466140f,
	0.01112034081946273144f,
	0.00986882845173894969f,
	0.00827877017294891340f,
	0.00637699396856634005f,
	0.00419550850221467840f,
	0.00177869987373837322f,
	-0.00082555395386654665f,
	-0.00355619139106229084f,
	-0.00635084332833611188f,
	-0.00913687669327088725f,
	-0.01184388842377634941f,
	-0.01439304433703247725f,
	-0.01670884572314251457f,
	-0.01871595360788791060f,
	-0.02033942489649480032f,
	-0.02151319954389355193f,
	-0.02217095459726720411f,
	-0.02225805172382782499f,
	-0.02172955174594901756f,
	-0.02054586704016144252f,
	-0.01868198728094428579f,
	-0.01612651265954864743f,
	-0.01287728390119748101f,
	-0.00894574096476025496f,
	-0.00436037879784812159f,
	0.00084023821120466334f,
	0.00660604212907755974f,
	0.01287214218204225068f,
	0.01956203302438026120f,
	0.02659300704251677666f,
	0.03387060042672338650f,
	0.04129356474076721628f,
	0.04875617685420141623f,
	0.05614905959147694497f,
	0.06336292526550180160f,
	0.07028860185508670200f,
	0.07681720941260644642f,
	0.08284936918997569399f,
	0.08828769563450682145f,
	0.09304781224894062563f,
	0.09705075517780124839f,
	0.10023454264389619617f,
	0.10254565000019172372f,
	0.10394850874580989497f,
	0.10441813534609947767f,
	0.10394850874580989497f,
	0.10254565000019172372f,
	0.10023454264389619617f,
	0.09705075517780124839f,
	0.09304781224894062563f,
	0.08828769563450682145f,
	0.08284936918997569399f,
	0.07681720941260644642f,
	0.07028860185508670200f,
	0.06336292526550180160f,
	0.05614905959147694497f,
	0.04875617685420141623f,
	0.04129356474076721628f,
	0.03387060042672338650f,
	0.02659300704251677666f,
	0.01956203302438026120f,
	0.01287214218204225068f,
	0.00660604212907755974f,
	0.00084023821120466334f,
	-0.00436037879784812159f,
	-0.00894574096476025496f,
	-0.01287728390119748101f,
	-0.01612651265954864743f,
	-0.01868198728094428579f,
	-0.02054586704016144252f,
	-0.02172955174594901756f,
	-0.02225805172382782499f,
	-0.02217095459726720411f,
	-0.02151319954389355193f,
	-0.02033942489649480032f,
	-0.01871595360788791060f,
	-0.01670884572314251457f,
	-0.01439304433703247725f,
	-0.01184388842377634941f,
	-0.00913687669327088725f,
	-0.00635084332833611188f,
	-0.00355619139106229084f,
	-0.00082555395386654665f,
	0.00177869987373837322f,
	0.00419550850221467840f,
	0.00637699396856634005f,
	0.00827877017294891340f,
	0.00986882845173894969f,
	0.01112034081946273144f,
	0.01201957192001466140f,
	0.01255830877472648849f,
	0.01274165590324968268f,
	0.01257958227088597052f,
	0.01209467034581716144f,
	0.01131180242891924835f,
	0.01026594777024173941f,
	0.00899261310973482192f,
	0.00753616908782961739f,
	0.00594060125538240467f,
	0.00425467564189114991f,
	0.00252502312089961578f,
	0.00079720365717879328f,
	-0.00088465535224722567f,
	-0.00247683369968309565f,
	-0.00394178783419616569f,
	-0.00524630112104608731f,
	-0.00636440350479003814f,
	-0.00727268812042745731f,
	-0.00795332094774038427f,
	-0.00839848859438984373f,
	-0.00860745777599359815f,
	-0.00858027672747722209f,
	-0.00832421895024035990f,
	-0.00785828592041203956f,
	-0.00720134191300308719f,
	-0.00637312932050280567f,
	-0.00540449562766091938f,
	-0.00432832903504513661f,
	-0.00316754016881003273f,
	-0.00196511218381902834f,
	-0.00074750617334680490f,
	0.00045062194073587094f,
	0.00159717493699539710f,
	0.00266663729095989281f,
	0.00362936703140398021f,
	0.00446732161081668782f,
	0.00515909698646572525f,
	0.00569384042514932756f,
	0.00605921348512520903f,
	0.00625350850557541971f,
	0.00627454051766952476f,
	0.00612867425751953149f,
	0.00582245751451044864f,
	0.00537108063511111764f,
	0.00478839895383255474f,
	0.00409565161990285784f,
	0.00331207464361695609f,
	0.00246339066993469082f,
	0.00157173086505566113f,
	0.00066372847437634077f,
	-0.00023864494720773338f,
	-0.00111007440097362145f,
	-0.00192996538719237285f,
	-0.00267642848078327540f,
	-0.00333115203754065590f,
	-0.00387732569881268788f,
	-0.00430432720003204403f,
	-0.00460436972480312168f,
	-0.00477603064590864830f,
	-0.00481822304547491718f,
	-0.00473021224181881250f,
	-0.00451316127749329041f,
	-0.00417498981526077083f,
	-0.00373322525549582215f,
	-0.00320569595551410376f,
	-0.00260262036934346590f,
	-0.00193243295402609964f,
	-0.00122487278964805496f,
	-0.00050732442462352121f,
	0.00021471061463893413f,
	0.00093190744973898807f,
	0.00158742964024669551f,
	0.00221027404170605042f,
	0.00275377271101419786f,
	0.00321672795267135842f,
	0.00358888716232179253f,
	0.00385570429810669748f,
	0.00401817237431850108f,
	0.00406637365429457585f,
	0.00400576663174091047f,
	0.00383316557616066467f,
	0.00355796635471669403f,
	0.00318247666178877358f,
	0.00272001967611711516f,
	0.00217778967729608756f,
	0.00157202114212711265f,
	0.00091254266260019923f,
	0.00021818695100586739f,
	-0.00049995562645775021f,
	-0.00122335318914068266f,
	-0.00194091647741515818f,
	-0.00263461180060850422f,
	-0.00329489407437547456f,
	-0.00390610983098922931f,
	-0.00446125148038516942f,
	-0.00494766532957854541f,
	-0.00536137211353130989f,
	-0.00569416567973387092f,
	-0.00594549547642638301f,
	-0.00611053843221215278f,
	-0.00619289644595245100f,
	-0.00619165365774415524f,
	-0.00611333808201909232f,
	-0.00596090985719547033f,
	-0.00574392404076935672f,
	-0.00546873276816104391f,
	-0.00514931429740205643f,
	-0.00479880981760322841f,
	-0.00444439656728895256f,
	-0.00412680221289675464f,
	-0.00393264864177109499f,
	-0.00403755979436868848f,
	-0.00483104839579957986f,
	-0.00716589506396039279f,
	0.00481248575344039864f
};

