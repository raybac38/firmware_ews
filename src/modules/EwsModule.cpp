#include "MeshService.h"
#include "MessageStore.h"
#include "NodeDB.h"
#include "PowerFSM.h"
#include "buzz.h"
#include "configuration.h"
#include "graphics/Screen.h"
#include "graphics/SharedUIDisplay.h"
#include "graphics/draw/MessageRenderer.h"
#include "main.h"
#include "EwsModule.h"

char a1[][10]={"Test","Alert","Update","All Clear",};
char a2[][70]={"Afghanistan" , "Albania" , "Antarctica" , "Algeria" , "American Samoa" , "Andorra" , "Angola" , "Antigua and Barbuda" , "Azerbaijan" , "Argentina" , "Australia" , "Austria" , "Bahamas (the)" , "Bahrain" , "Bangladesh" , "Armenia" , "Barbados" , "Belgium" , "Bermuda" , "Bhutan" , "Bolivia (Plurinational State of)" , "Bosnia and Herzegovina" , "Botswana" , "Bouvet Island" , "Brazil" , "Belize" , "British Indian Ocean Territory (the)" , "Solomon Islands" , "Virgin Islands (British)" , "Brunei Darussalam" , "Bulgaria" , "Myanmar" , "Burundi" , "Belarus" , "Cambodia" , "Cameroon" , "Canada" , "Cabo Verde" , "Cayman Islands (the)" , "Central African Republic (the)" , "Sri Lanka" , "Chad" , "Chile" , "China" , "Taiwan (Province of China)" , "Christmas Island" , "Cocos (Keeling) Islands (the)" , "Colombia" , "Comoros (the)" , "Mayotte" , "Congo (the)" , "Congo (the Democratic Republic of the)" , "Cook Islands (the)" , "Costa Rica" , "Croatia" , "Cuba" , "Cyprus" , "Czechia" , "Benin" , "Denmark" , "Dominica" , "Dominican Republic (the)" , "Ecuador" , "El Salvador" , "Equatorial Guinea" , "Ethiopia" , "Eritrea" , "Estonia" , "Faroe Islands (the)" , "Falkland Islands (the) [Malvinas]" , "South Georgia and the South Sandwich Islands" , "Fiji" , "Finland" , "Åland Islands" , "France" , "French Guiana" , "French Polynesia" , "French Southern Territories (the)" , "Djibouti" , "Gabon" , "Georgia" , "Gambia (the)" , "Palestine, State of" , "Germany" , "Ghana" , "Gibraltar" , "Kiribati" , "Greece" , "Greenland" , "Grenada" , "Guadeloupe" , "Guam" , "Guatemala" , "Guinea" , "Guyana" , "Haiti" , "Heard Island and McDonald Islands" , "Holy See (the)" , "Honduras" , "Hong Kong" , "Hungary" , "Iceland" , "India" , "Indonesia" , "Iran (Islamic Republic of)" , "Iraq" , "Ireland" , "Israel" , "Italy" , "Côte d'Ivoire" , "Jamaica" , "Japan" , "Kazakhstan" , "Jordan" , "Kenya" , "Korea (the Democratic People's Republic of)" , "Korea (the Republic of)" , "Kuwait" , "Kyrgyzstan" , "Lao People's Democratic Republic (the)" , "Lebanon" , "Lesotho" , "Latvia" , "Liberia" , "Libya" , "Liechtenstein" , "Lithuania" , "Luxembourg" , "Macao" , "Madagascar" , "Malawi" , "Malaysia" , "Maldives" , "Mali" , "Malta" , "Martinique" , "Mauritania" , "Mauritius" , "Mexico" , "Monaco" , "Mongolia" , "Moldova (the Republic of)" , "Montenegro" , "Montserrat" , "Morocco" , "Mozambique" , "Oman" , "Namibia" , "Nauru" , "Nepal" , "Netherlands (the)" , "Curaçao" , "Aruba" , "Sint Maarten (Dutch part)" , "Bonaire, Sint Eustatius and Saba" , "New Caledonia" , "Vanuatu" , "New Zealand" , "Nicaragua" , "Niger (the)" , "Nigeria" , "Niue" , "Norfolk Island" , "Norway" , "Northern Mariana Islands (the)" , "United States Minor Outlying Islands (the)" , "Micronesia (Federated States of)" , "Marshall Islands (the)" , "Palau" , "Pakistan" , "Panama" , "Papua New Guinea" , "Paraguay" , "Peru" , "Philippines (the)" , "Pitcairn" , "Poland" , "Portugal" , "Guinea-Bissau" , "Timor-Leste" , "Puerto Rico" , "Qatar" , "Réunion" , "Romania" , "Russian Federation (the)" , "Rwanda" , "Saint Barthélemy" , "Saint Helena, Ascension and Tristan da Cunha" , "Saint Kitts and Nevis" , "Anguilla" , "Saint Lucia" , "Saint Martin (French part)" , "Saint Pierre and Miquelon" , "Saint Vincent and the Grenadines" , "San Marino" , "Sao Tome and Principe" , "Saudi Arabia" , "Senegal" , "Serbia" , "Seychelles" , "Sierra Leone" , "Singapore" , "Slovakia" , "Viet Nam" , "Slovenia" , "Somalia" , "South Africa" , "Zimbabwe" , "Spain" , "South Sudan" , "Sudan (the)" , "Western Sahara*" , "Suriname" , "Svalbard and Jan Mayen" , "Eswatini" , "Sweden" , "Switzerland" , "Syrian Arab Republic (the)" , "Tajikistan" , "Thailand" , "Togo" , "Tokelau" , "Tonga" , "Trinidad and Tobago" , "United Arab Emirates (the)" , "Tunisia" , "Turkey" , "Turkmenistan" , "Turks and Caicos Islands (the)" , "Tuvalu" , "Uganda" , "Ukraine" , "North Macedonia" , "Egypt" , "United Kingdom of Great Britain and Northern Ireland (the)" , "Guernsey" , "Jersey" , "Isle of Man" , "Tanzania, the United Republic of" , "United States of America (the)" , "Virgin Islands (U.S.)" , "Burkina Faso" , "Uruguay" , "Uzbekistan" , "Venezuela (Bolivarian Republic of)" , "Wallis and Futuna" , "Samoa" , "Yemen" , "Zambia" , "EU Organisations" , "UN Organisations" , "International"};
char a4[][700]={{"CBRNE : Air strikeAttack performed by an aircraft, usually of military type, either by bombing (or similar), firing guns or missiles."} ,
 {"CBRNE : Attack on IT systemsIntentional attempt to expose, alter, disable, destroy, steal or gain unauthorized access to or make unauthorised use of IT equipment."} ,
 {"CBRNE : Attack with nuclear weaponsFrom www.dhs.gov 'Attack performed with a device producing a nuclear explosion."} ,
 {"CBRNE : Biological hazardPresence of hazardous biological materials that present a risk or potential risk to the health of humans, animals, plants, or the environment."} ,
 {"CBRNE : Chemical hazardPresence of hazardous chemical materials that present a risk or potential risk to the health of humans, animals, plants, or the environment."} ,
 {"CBRNE : Explosive hazardPresence of hazardous explosive materials that present a risk or potential risk to the health of humans, animals, plants, or the environment."} ,
 {"CBRNE : Meteorite impactMeteorite entering from space into the earth atmosphere."} ,
 {"CBRNE : Missile attackMissile launch."} ,
 {"CBRNE : Nuclear hazardPresence of hazardous nuclear materials that present a risk or potential risk to the health of humans, animals, plants, or the environment."} ,
 {"CBRNE : Nuclear power station accidentAccident occurring at an installation where power is generated by a nuclear reactor."} ,
 {"CBRNE : Radiological hazardPresence of hazardous radioactive materials that present a risk or potential risk to the health of humans, animals, plants, or the environment."} ,
 {"CBRNE : Satellite/space re-entry debrisSatellite or parts of a satellite or launcher or space vehicle entering or re-entering from space into the earth atmosphere."} ,
 {"CBRNE : Siren testTest of a warning device emitting a loud noise."} ,
 {"ENVIRONMENT : Acid rainRain containing dissolved acidifying compounds, resulting from chemical pollution of the atmosphere by sulphur and nitrogen compounds. When deposited, these increase the acidity of the soil and water causing agricultural and ecological damage."} ,
 {"ENVIRONMENT : Air pollutionPrecise threshold is according to each local standard."} ,
 {"ENVIRONMENT : Contaminated drinking waterDrinking water containing contaminants (germs and/or chemicals) above the quality standard. Precise threshold according to each local standard."} ,
 {"ENVIRONMENT : Gas leakUncontrolled release of natural gas or gaseous product in the environment."} ,
 {"ENVIRONMENT : Marine pollutionMarine pollution occurs when substances used or spread by humans, such as industrial, agricultural and residential waste, particles, noise, excess carbon dioxide or invasive organisms enter the ocean and cause harmful effects there. Precise threshold is according to each local standard."} ,
 {"ENVIRONMENT : Noise pollutionDisturbing or unwanted noise that may present a potential risk to the health of humans, animals and wildlife."} ,
 {"ENVIRONMENT : Plague of insectsInfestation of insects or pervasive influx and development of insects or parasites affecting humans, animals, crops and materials."} ,
 {"ENVIRONMENT : River pollutionContamination of water in rivers, usually as a result of human activities, in such a manner that negatively affects its legitimate uses."} ,
 {"ENVIRONMENT : Suspended dustMore general, particulates are microscopic solid particles suspended in the air. The source of the particulate matter can be natural or anthropogenic having adverse effect on human health. The IARC and WHO designate airborne particulates as a Group 1 carcinogen. Particulates are the most harmful form of air pollution due to their ability to penetrate deep into the lungs, blood streams and brain, causing health problems including heart attacks, respiratory disease, and premature death."} ,
 {"ENVIRONMENT : UV radiationPrecise threshold is according to each local standard."} ,
 {"FIRE : ConflagrationA large and destructive fire that threatens human life, health, and/or property."} ,
 {"FIRE : Fire brigade deploymentOperation of firefighters in response to a fire or other emergency report. Note: Definition may vary, depending on the responsibility of the fire brigade in each country"} ,
 {"FIRE : Fire gasesPotentially dangerous gases emitted from a fire."} ,
 {"FIRE : Forest fireA type of wildfire in a wooded area."} ,
 {"FIRE : FumesAn often-noxious suspension of particles in the air."} ,
 {"FIRE : Odour nuisanceProlonged and offensive smell leading to the impairment of human well-being over a certain period of time at regular or irregular intervals."} ,
 {"FIRE : Risk of fireIncreased likelihood of accidental fire."} ,
 {"FIRE : Structure fire / Industrial fire Fire affecting the structural parts of a building or a fire affecting an industrial site."} ,
 {"GEO : Ash fallFine (less than 4 mm in diameter) unconsolidated volcanic debris blown into the atmosphere during an eruption can remain airborne for long periods of time and travel considerable distance from the source."} ,
 {"GEO : Avalanche riskA large mass of loosened earth material, snow, or ice that slides, flows or falls rapidly down a mountainside under the force of gravity. Snow Avalanche: Rapid downslope movement of a mix of snow and ice. Debris Avalanche: The sudden and very rapid downslope movement of unsorted mass of rock and soil. There are two general types of debris avalanchesa cold debris avalanche usually results from an unstable slope suddenly collapsing whereas a hot debris avalanche results from volcanic activity leading to slope instability and collapse."} ,
 {"GEO : Crack in the ground/sinkholeCollapse of the land surface due to the dissolving of the subsurface rocks such as limestone or carbonate rock by water."} ,
 {"GEO : Debris flowTypes of landslides that occur when heavy rain or rapid snow/ice melt send large amounts of vegetation, mud, or rock downslope by gravitational forces. Includes mud flow, rock fall."} ,
 {"GEO : Earthquake Sudden movement of a block of the Earth’s crust along a geological fault and associated ground shaking."} ,
 {"GEO : Geomagnetic or solar stormA type of extra-terrestrial hazard caused by solar wind shockwaves that temporarily disturb the Earth’s magnetosphere. Geomagnetic storms can disrupt power grids, spacecraft operations, and satellite communications."} ,
 {"GEO : Glacial ice avalancheIce calving at end of a glacier."} ,
 {"GEO : Landslide Independent of the presence of water, mass movement may also be triggered by earthquakes."} ,
 {"GEO : Lava flowThe ejected magma that moves as a liquid mass downslope from a volcano during an eruption."} ,
 {"GEO : Pyroclastic flowExtremely hot gases, ash, and other materials of more than 1,000 degrees Celsius that rapidly flow down the flank of a volcano (more than 700 km/h) during an eruption."} ,
 {"GEO : SnowdriftsMass of snow heaped up by the wind and deposited along an obstruction or an irregularity of the terrain."} ,
 {"GEO : Tidal waveShallow water wave caused by the gravitational interactions between the Sun, Moon, and Earth. (from USGS)"} ,
 {"GEO : TsunamiA series of waves (with long wavelengths when traveling across the deep ocean) that are generated by a displacement of massive amounts of water through underwater earthquakes, volcanic eruptions or landslides. Tsunami waves travel at very high speed across the ocean but as they begin to reach shallow water they slow down and the wave grows steeper."} ,
 {"GEO : Volcanic mud flow(Also known as Lahar) A mud flow resulting from a volcanic event. Hot or cold mixture of earthen material flowing on the slope of a volcano either during or between volcanic eruptions."} ,
 {"GEO : Volcano eruptionA type of volcanic event near an opening/vent in the Earth’s surface including volcanic eruptions of lava, ash, hot vapour, gas, and pyroclastic material."} ,
 {"GEO : Wind/wave/storm surgeAn abnormal rise in sea level generated by a tropical cyclone or other intense storms."} ,
 {"HEALTH : EpizooticAn epidemic outbreak of disease in an animal population, often with the implication that it may extend to humans."} ,
 {"HEALTH : Food safety alertPresence of unsafe food containing harmful bacteria, viruses, parasites or chemical substances that present a risk to the health of humans, animals, plants or the environment."} ,
 {"HEALTH : Health hazardPotential source of danger for individual's health."} ,
 {"HEALTH : PandemiAn epidemic of an infectious disease that has spread across a large region, for instance multiple continents or worldwide, affecting a substantial number of people. A widespread endemic disease with a stable number of infected people is not a pandemic. Widespread endemic diseases with a stable number of infected people such as recurrences of seasonal influenza are generally excluded as they occur simultaneously in large regions of the globe rather than being spread worldwide."} ,
 {"HEALTH : Pest infestation(from GEMET )1) The occurrence of one or more pest species in an area or location where their numbers and impact are currently or potentially at intolerable levels. 2) A sudden increase in destructiveness or population numbers of a pest species in a given area."} ,
 {"HEALTH : Risk of infectionPresent of infectious agent(s) that present a risk or potential risk to the health of humans, animals, plants, or the environment."} ,
 {"INFRASTRUCTURE : Building collapseSudden failure of the building structure resulting in its partial or total destruction."} ,
 {"INFRASTRUCTURE : Emergency number outageInterruption or failure of emergency number service."} ,
 {"INFRASTRUCTURE : Gas supply outageInterruption or failure of gas supply service."} ,
 {"INFRASTRUCTURE : Outage of IT systemsInterruption or failure of IT systems services."} ,
 {"INFRASTRUCTURE : Power outageInterruption or failure of electricity distribution service."} ,
 {"INFRASTRUCTURE : Raw sewageRelease in the environment of untreated wastewater."} ,
 {"INFRASTRUCTURE : Telephone line outageInterruption or failure of telephone service."} ,
 {"MET : Black IceWMO definition: (1) Thin, new ice on freshwater or saltwater, appearing dark in colour because of its transparency, which is a result of its columnar grain structure. On lakes, black ice is commonly overlain by white ice formed from refrozen snow or slush. (2) A popular alternative for glaze. A thin sheet of ice, relatively dark in appearance, may form when light rain or drizzle falls on a road surface that is at a temperature below 0°C or, alternatively, when water already on the road surface subsequently freezes when the temperature thereof falls below freezing point. It may also be formed when supercooled fog droplets are intercepted by buildings, fences and vegetation."} ,
 {"MET : Coastal floodingOccurs when dry and low-lying land is submerged by seawater."} ,
 {"MET : Cold waveExtreme cold and low temperatures."} ,
 {"MET : DerechoWidespread and usually fast-moving windstorms associated with convection/convective storm. Derechos include downburst and straight-line winds. The damage from derechos is often confused with the damage from tornadoes."} ,
 {"MET : DroughtAn extended period of unusually low precipitation that produces a shortage of water for people, animals and plants. Drought is different from most other hazards in that it develops slowly, sometimes even over years, and its onset is generally difficult to detect."} ,
 {"MET : Dust stormStrong winds carry particles of sand aloft, but generally confined to less than 50 feet (15 m), especially common in arid and semi-arid environments. A dust storm is also characterised by strong winds but carries smaller particles of dust rather than sand over an extensive area."} ,
 {"MET : Floating ice / icebergsFloating ice in rivers or icebergs in the open sea"} ,
 {"MET : FloodA general term for the overflow of water from a stream channel onto normally dry land in the floodplain (riverine flooding), higher-than normal levels along the coast and in lakes or reservoirs (coastal flooding) as well as ponding of water at or near the point where the rain fell (flash floods)."} ,
 {"MET : Fog A suspension of very small, usually microscopic water droplets in the air, reducing visibility at the Earth’s surface."} ,
 {"MET : Hail Solid precipitation in the form of irregular pellets or balls of ice more than 5 mm in diameter."} ,
 {"MET : Heat waveA general term for temperature variations above (extreme heat)."} ,
 {"MET : LightningA high-voltage, visible electrical discharge produced by a thunderstorm and followed by the sound of thunder."} ,
 {"MET : PollensPollens that can cause human allergies are those of anemophilous plants (pollen is dispersed by air currents.) Such plants produce large quantities of lightweight pollen (because wind dispersal is random and the likelihood of one pollen grain landing on another flower is small), which can be carried for great distances and are easily inhaled by humans."} ,
 {"MET : Rainfall Rainfall greater than or equal to 50mm in past 24 hours. Note: Precise threshold is according to each local standard."} ,
 {"MET : Snow storm / blizzardA low-pressure system in winter months with significant accumulations of snow, freezing rain, sleet or ice. A blizzard is a severe snowstorm with winds exceeding 35 mph (56 km/h) for three or more hours, producing reduced visibility (less than .25 mile (400 m)."} ,
 {"MET : SnowfallSnowfall greater than or equal to 50mm in past 24 hours. Note: Precise threshold is according to each local standard."} ,
 {"MET : Storm or thunderstormMeteorological event generating winds equal or higher than 10 on the Beaufort scale."} ,
 {"MET : ThawingGradual warning causing ground ice to degrade, potentially leading the soil surface to collapse."} ,
 {"MET : TornadoA violently rotating column of air that reaches the ground or open water (waterspout)."} ,
 {"MET : Tropical cyclone (hurricane)A tropical cyclone originates over tropical or subtropical waters. It is characterised by a warm-core, non-frontal synoptic-scale cyclone with a low-pressure centre, spiral rain bands and strong winds. Depending on their location, tropical cyclones are referred to as hurricanes (Atlantic, Northeast Pacific), typhoons (Northwest Pacific), or cyclones (South Pacific and Indian Ocean). With a minimum wind speed of 119km/h (or 74 miles/h) a tropical storm in the Atlantic or Northeast Pacific is called a hurricane."} ,
 {"MET : Wind chill/frostFrost is the consequence of radiative cooling resulting in the formation of thin ice crystals on the ground or other surfaces in the form of needles, feathers, scales, or fans. Frost occurs when the temperature of surfaces is below freezing and water vapor from humid air forms solid deposits on the cold surface. Freeze occurs when the air temperature is at (32˚F/0˚C) or below over a widespread area for a climatologically significant period of time. Use of the term is usually restricted to advective situations or to occasions when wind or other conditions prevent frost. Frost and freeze are particularly damaging during the crop growing season."} ,
 {"MET : Tropical cyclone (typhoon)A tropical cyclone originates over tropical or subtropical waters. It is characterised by a warm-core, non-frontal synoptic-scale cyclone with a low-pressure centre, spiral rain bands and strong winds. Depending on their location, tropical cyclones are referred to as hurricanes (Atlantic, Northeast Pacific), typhoons (Northwest Pacific), or cyclones (South Pacific and Indian Ocean). With a minimum wind speed of 119km/h (or 74 miles/h) a tropical storm in the Atlantic or Northeast Pacific is called a hurricane."} ,
 {"RESCUE : Dam failure or bursting of a damIncident at a dam potentially leading to the uncontrolled release of the dam content"} ,
 {"RESCUE : Dike failure or bursting of a dikeIncident at a dike potentially leading to the uncontrolled release of water"} ,
 {"RESCUE : Explosive ordnance disposalActivity to render safe all types of ordnance, including explosive, chemical and biological. It covers land and underwater location, identification, render-safe, and recovery (or disposal) of ordnance."} ,
 {"RESCUE : Factory accidentIncident at an industrial site affecting the surrounding area"} ,
 {"RESCUE : Mine hazard Any of the dangers peculiar to the winning and working of coal and minerals. These include collapse of ground, explosion of released gas, inundation by water, spontaneous combustion, inhalation of dust and poisonous gases, etc."} ,
 {"SAFETY : Bomb/ammunition discoveryUnexpected presence of bomb or ammunition"} ,
 {"SAFETY : DemonstrationA march or gathering of people taking part in to show their opposition to something or their support for something"} ,
 {"SAFETY : Hazardous material accidentAn unexpected uncontrolled release of substances that have the potential to harm a person or the environment upon contact."} ,
 {"SAFETY : Life Threatening situationEmergency situation that requires immediate intervention to save the life of the persons concerned."} ,
 {"SAFETY : Major eventPlanned happening which may generate significant disruption in road traffic or transport"} ,
 {"SAFETY : Missing person/abductionUnaccounted person whose health status (alive/dead) cannot be confirmed."} ,
 {"SAFETY : Risk of explosionIntentional use of explosive materials aiming at killing or damaging the health of humans, animals, plants, or the environment."} ,
 {"SAFETY : Safety warningAnnouncement of a potentially dangerous situation or event to the public impacting their safety."} ,
 {"SAFETY : Undefined flying objectPresence of an unidentified flying object which may present a risk or potential risk to the health of humans, animals, plants, or the environment. Hurricanes and typhoons are the same weather phenomenon. A tropical cyclone is a generic term used to describe a rotating, organized system of clouds and thunderstorms that originates over tropical or subtropical waters and has closed, low-level circulation. The classification as a hurricane, typhoon or tropical cyclone depends upon where the storm originates in the world. Although, in this list of hazards hurricanes and typhoons are identified separately."} ,
 {"SAFETY : Unidentified animalPresence of an unidentified animal which may present a risk or a potential risk to the health of humans, animals, plants, or the environment."} ,
 {"SECURITY : Chemical attackIntentional use of dangerous chemical materials aiming at killing or damaging the health of humans, animals, plants, or the environment."} ,
 {"SECURITY : Guerrilla attackParamilitary armed forces carrying violent actions."} ,
 {"SECURITY : HijackAirplane or other vehicle under the control of hijackers"} ,
 {"SECURITY : Shooting or danger due to weaponsDangerous use of firearm(s) or weapons in a populated area."} ,
 {"SECURITY : Special forces attackMilitary armed forces carrying violent actions."} ,
 {"SECURITY : TerrorismTerrorist action aiming at generating a high number of victims or major material damage."} ,
 {"TRANSPORT : Aircraft crashAircraft crash"} ,
 {"TRANSPORT : Bridge collapseStructural failure of a bridge resulting in its partial or total destruction."} ,
 {"TRANSPORT : Dangerous goods accidentAccident occurrence associated with and related to the conveyance of dangerous goods by air, road, inland waterways and sea, which results in fatal or serious injury to a person or major damage to property or environment."} ,
 {"TRANSPORT : Inland waterway transport accidentShip accident on an inland waterway."} ,
 {"TRANSPORT : Nautical disaster/Maritime/Marine SecuritySinking ship or any other event occurring at sea which may present of security or safety risk."} ,
 {"TRANSPORT : Oil spillLeak of oil or pollutant from a ship or other transportation mean resulting in pollution."} ,
 {"TRANSPORT : Road traffic incidentAnnouncement of road traffic disruption."} ,
 {"TRANSPORT : Train/rail accidentAccident occurring on a railway and involving train(s) and/or other vehicles."} ,
 {"TRANSPORT : Tunnel accidentCar crash or railway accident occurring in a tunnel."} ,
 {"OTHER : Test alertTest alert message for end-to-end testing."} };
char a5[][60]= {"Unknown" , "Moderate : Possible threat to life or property" , "Severe : Significant threat to life or property" , "Extreme : Extraordinary threat to life or property" };
char a6[][15]={"Current","Next"};
char a8[][20]={"Duration unknown" , "Duration < 6" , "6 <= Duration < 12" , "12 <= Duration < 24" };
char a11a[][220]= {"" , "You are in the danger zone, leave the area immediately. Listen to radio or media for directions and information." , "You are in the danger zone, leave the area immediately and reach the evacuation point indicated by the area plotted in yellow. Listen to radio or media for directions and information." , "Seek shelter in a building immediately. Stay under cover and stay informed." , "Seek out a cellar or interior rooms on lower floors." , "If you are in an alpine terrain, start descending immediately and seek for shelter." , "Quickly move into interior rooms. If you are in a vehicle: Stop driving immediately on the edge of the road. If a building is nearby, seek shelter in that building." , "If you are in open terrain and you cannot find shelter, lie face-down on the ground and protect your head and neck with your hands, in a hollow where possible" , "Prepare for evacuation. Take only the essentials with you, especially ID cards, passport, credit cards and cash. Evacuate only after the instruction of the emergency authorities." , "Prepare emergency food and relief material: Check and restock your equipment and supplies of water, food, medicine, cash and batteries." , "Stay away from glass surfaces such as windows and glass doors. There is a risk of injury from glass splinters." , "Reduce your power consumption to a minimum." , "Reduce your water consumption to a minimum." , "Boil water before drinking it or using it in the kitchen." , "Keep at least one metre away from any conversation partners. Avoid physical contact with other people such as kissing and shaking hands. Wash your hands regularly and thoroughly." , "Do not drink any tap water. Avoid any skin contact with tap water. Only drink mineral water from a bottle. Turn off the water supply to your house." , "Watch out for escaping gas. This can be indicated by hissing noises or a typical gas odour. Do not use matches, lighters or the like: naked flames in combination with leaking gas can lead to explosions and fires." , "Do not go outside and do not use your car." , "Do not touch any objects that seem suspicious to you. Debris can cause additional hazards such as fires and explosions. Inform the emergency services about damage and debris." , "Do not enter smoke-filled rooms. Deadly gases can form there." , "Do not enter cellars or underground car parks." , "Do not leave pets or livestock outside." , "Do not touch any dead animals. Report any findings of dead wild animals to the authorities." , "Avoid driving" , "Avoid all items with metal parts such as umbrellas and bicycles. Do not bathe or shower during a thunderstorm. Bathing and showering can be life-threatening." , "Avoid rooms directly underneath the roof truss. Avoid very large rooms, such as halls, in which the ceiling is not supported by pillars." , "Avoid going outdoors. Keep away from trees, towers and masts. Keep at least 20" , "Avoid the danger area" , "Avoid going out when it is not necessary" , "This is only a test. You do not have to take any action or to adopt any particular sheltering behaviour" , "This replaces the warning previously in effect for this area." , "Conditions have improved and are no longer expected to meet alert criteria." };
char a11b[][450]= {"" , "Check with the weather services and local authorities for additional information" , "Find out the location of the information points set up by the authorities on official channels (radio, internet, TV, social networks…)" , "Sensitive or vulnerable people should not go out unless they must." , "Rescue operation under process by security forces and emergency services. Avoid moving to facilitate security and emergency actions." , "Protect the most vulnerable and hear from your loved ones. Be aware of their special needs and support, as required. If you notice distressed or vulnerable persons, call the emergency services. Provide first aid if necessary but do not put yourself in any danger." , "Pay attention to announcements made by the police, fire brigade and by officials." , "Stay aware, keep listening to official instructions broadcast on the radio, television, websites and social networks pages" , "If you need help leaving your home, call the emergency services." , "Only make phone calls in serious emergencies to avoid overloading the mobile network." , "Extreme intensity weather phenomena expected. The weather is very dangerous and implies high level of threat to health, even the life hazard. BE AWARE and keep up to date with the latest weather forecast." , "Severe weather expected. BE PREPARED. Take precautions and keep up to date with the latest weather forecast. Severe damages to people and properties may occur, especially to those vulnerable or in exposed areas." , "Moderate intensity weather phenomena expected. BE AWARE, keep up to date with the latest weather forecast. Moderate damages to people and properties may occur, especially to those vulnerable or in exposed areas" , "BE PREPARED to protect yourself and your property. Flooding of properties and transport networks is expected. Disruption to power, communications and water supplies are possible. Evacuation may be required. Dangerous driving conditions due to reduced visibility and aquaplaning" , "Do not go near or in flooded waters. Do not walk or drive on a submerged road. Flood waves may surprise you, the river bank may collapse or you could be sucked in a manhole or hit by a floating debris. Keep drains and shafts clear so that the water can drain away. Secure and/or move assets away from vulnerable area (car along the river, basements)." , "Take shelter in the most resistant part of a permanent building, a municipal shelter if possible, and keep away from windows. BE AWARE of the “eye of the storm”, the calm area in its centre. It will be followed by an inversion and the strengthening of winds. Do not go outside and do not use your car. Wait until the alert is over." , "TAKE PRECAUTIONS, High temperatures are expected. Protect yourself from the heat and avoid physical and sports activities. Wet your body several times a day. Drink plenty of water and eat light food." , "Forest fire danger. Under these conditions fires may develop and spread rapidly resulting in damage to property and possible loss of human and/or animal life. Do not throw away any burning cigarettes or matches to the environment. Do not make a fire outdoors. Do not light any fireworks. Do not barbeque in open places. Vegetation is easily ignited and large areas may be affected. Follow the instructions from the local authorities." , "Risks of fire. Use permanent fireplaces when barbecuing. Make sure your fire is completely extinguished before you leave. Only light fireworks with the permission of the municipality, keep a safe distance from the forest and have water to hand." , "Keep as far away as possible from coastal areas, beaches and rivers. Get immediately to the highest ground possible and wait until the alert is over. If you are in danger of being overtaken by waves, climb onto a roof or up a solid tree, or cling on to a floating object carried along by the water." , "Do not go to sea and keep as far away as possible from the coast and wait until the alert is over. If you are at sea, don’t return to port. Keep away from the coast. Waves are much less dangerous out at sea." , "Leave the affected area immediately and seek higher ground or move to higher parts of the building. Listen to radio or media for directions and information" , "Indoors: during the quake, take shelter near a wall or a solid piece of furniture. Outside: during the quake, keep away from anything that might collapse. In a car: during the quake, stop as far away from buildings as you can. After, be prepared for aftershocks. If you are indoor, leave by the stairs." , "Leave the impact site immediately and cover your mouth and nose with improvised respiratory protection (cloth, garment, surgical mask). This protects you from dust, but not from gaseous hazardous substances. Seek out a building. Move wherever possible at a right angle to the wind direction as this is the quickest way to leave the danger zone with a possible cloud of hazardous substances." , "Switch off the ventilation and air conditioning systems. Close all windows, doors and shutters. Cover your mouth and nose and breathe through a facemask or an improvised respiratory protection (cloth, garment, surgical mask) if the air is filled with smoke and ashes" , "Have iodine tablets ready. DO NOT take the iodine tablets now. If this becomes necessary, we will inform you in good time." , "Take the iodine tablets NOW according to the package insert." , "Avoid watering your plants during the hottest hours, avoid using water for secondary uses such as washing your car." , "Seek shelter if you cannot leave the area immediately." , "reserved" , "reserved" , "This replaces the warning previously in effect for this area" };
//a9 pas utiliser voir comment l'integrer

char* str_a2(int i){
    if(i<=248){
        return a2[i];
    } else if(i<500){
       return (char*)"Malformed region";
    } else{
        return a2[i-251];
    }
}

//!!!half days
void str_dayHour(char*date, int i){
    if (i==0 || i>=10081){date= (char*)"Malformed time of the week"; return;}
    char* day;
    char* half_day;
    int t=i-1;
    switch (t/1440){
    case 0:
        day=(char*)"MONDAY";
        break;
    case 1:
        day=(char*)"TUESDAY";
        break;
    case 2:
        day=(char*)"WEDNESDAY";
        break;
    case 3:
        day=(char*)"THURSDAY";
        break;
    case 4:
        day=(char*)"FRIDAY";
        break;
    case 5:
        day=(char*)"SATURDAY";
        break;
    case 6:
        day=(char*)"SUNDAY";
        break;
    }
    t = t%1440;
    if (t>720){
        half_day=(char*)"pm";
        t=t-720;
    } else {
        half_day=(char*)"am";
    }
    int hour = t/60;
    int minute = t%60;
    sprintf(date,"%s - %d:%d %s\0",(char*)day,hour,minute, half_day);

}

char* translate_eng(int a1_, int a2_, int a4_, int a5_, int a6_, int a7_, int a8_, int a11a_, int a11b_)
{    
    char* msg_eng=(char*)malloc(10000*sizeof(char));
    char* typeMsg=a1[a1_];
    char* region=str_a2(a2_);
    char* onsetWeek=a6[a6_];
    char dayHour[50];
    str_dayHour(dayHour,a7_);
    char* hazardType=a4[a4_];
    char* severity=a5[a5_];
    char* duration=a8[a8_];
    char* guidanceInstructionA=a11a[a11a_];
    char* guidanceInstructionB=a11b[a11b_];

    
    sprintf(msg_eng,"%s\n%s\n%s week\n%s\n%s\nSeverity: %s\n%s\n%s\n%s\0", typeMsg, region, onsetWeek, dayHour, hazardType, severity, duration, guidanceInstructionA, guidanceInstructionB);
    return msg_eng;

}

ProcessMessage EwsModule::handleReceived(const meshtastic_MeshPacket &mp)
{
#if defined(DEBUG_PORT) && !defined(DEBUG_MUTE)
    auto &p = mp.decoded;
LOG_INFO("Received ews msg from=0x%0x", mp.from, mp.id);
#endif
    return ProcessMessage::STOP;
}

bool EwsModule::wantPacket(const meshtastic_MeshPacket *p)
{
    return p->decoded.portnum == meshtastic_PortNum_EWS;
}