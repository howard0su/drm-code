/******************************************************************************\
 * British Broadcasting Corporation
 * Copyright (c) 2009
 *
 * Author(s):
 *	 Julian Cable, Volker Fischer, Andrea Russo
 *
 * Description:
 *  QT4 Model for managing schedule data
 *
 ******************************************************************************
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 *
\******************************************************************************/

#include "ScheduleModel.h"
#include "../tables/TableStations.h"
#include <QIcon>
#include <QStandardItem>
#include <iostream>

/* Location of the newest DRM schedule ini-file "DRMSchedule.ini". This file
   is generated by Klaus Schneider which is the administrator of
   www.drm-dx.de */
const char* DRM_SCHEDULE_UPDATE_URL = "ftp://216.92.35.131/DRMSchedule.ini";
const char* AM_SCHEDULE_UPDATE_URL = "http://www.eibispace.de/dx/sked-%1%2.csv";

/* Name for DRM and AM schedule file. If you change something here, make sure
   that you also change the strings and help texts!  */
const char* DRMSCHEDULE_INI_FILE_NAME = "DRMSchedule.ini";
const char* AMSCHEDULE_INI_FILE_NAME = "AMSchedule.ini";

CTxSchedule::CTxSchedule(): ScheduleTable(), iSecondsPreview(0),
BitmCubeGreen(13,13), BitmCubeYellow(13,13), BitmCubeRed(13,13),
BitmCubeOrange(13,13), BitmCubePink(13,13)
{
	/* Create bitmaps */
	BitmCubeGreen.fill(QColor(0, 255, 0));
	BitmCubeYellow.fill(QColor(255, 255, 0));
	BitmCubeRed.fill(QColor(255, 0, 0));
	BitmCubeOrange.fill(QColor(255, 128, 0));
	BitmCubePink.fill(QColor(255, 128, 128));
}

int
CTxSchedule::rowCount ( const QModelIndex&) const
{
	return ScheduleTable.size();
}

int
CTxSchedule::columnCount ( const QModelIndex&) const
{
	return 9;
}

QVariant
CTxSchedule::data ( const QModelIndex& index, int role) const
{
	const CScheduleItem& item = ScheduleTable[index.row()];
	switch(role)
	{
	case Qt::DecorationRole:
		if(index.column()==0)
		{
			/* Check, if station is currently transmitting. If yes, set
			   special pixmap */
			QIcon icon;
			switch (item.state)
			{
				case CScheduleItem::IS_ACTIVE:
					icon.addPixmap(BitmCubeGreen);
					break;
				case CScheduleItem::IS_PREVIEW:
					icon.addPixmap(BitmCubeOrange);
					break;
				case CScheduleItem::IS_SOON_INACTIVE:
					icon.addPixmap(BitmCubePink);
					break;
				default:
					icon.addPixmap(BitmCubeRed);
			}
			return icon;
		}
		break;
	case Qt::DisplayRole:
		switch(index.column())
		{
			case 0:
				return item.strName.c_str();
			break;
			case 1:
				return QString().sprintf("%04d-%04d",item.GetStartTimeNum(),item.GetStopTimeNum());
				break;
			case 2:
				return item.iFreq;
				break;
			case 3:
				/* Get power of the station. We have to do a special treatment
				   here, because we want to avoid having a "0" in the list when
				   a "?" was in the schedule-ini-file */
				if (item.rPower < 0.001) // 1W, to avoid equality test on floating point
					return "?";
				else
					return item.rPower;
				break;
			case 4:
				return item.strCountry.c_str();
				break;
			case 5:
				return item.strSite.c_str();
				break;
			case 6:
				return item.strTarget.c_str();
				break;
			case 7:
				return item.strLanguage.c_str();
				break;
			case 8:
				return item.strDaysShow;
				break;
		}
		break;
	case Qt::UserRole:
		{
		QString r = QString("%1#%2#%3#%4")
			.arg(item.strTarget.c_str())
			.arg(item.strCountry.c_str())
			.arg(item.strLanguage.c_str())
			.arg((item.state==CScheduleItem::IS_INACTIVE)?0:1);
			return r;
		}
		break;
	case Qt::TextAlignmentRole:
		switch(index.column())
		{
			case 2:
			case 3:
				return QVariant(Qt::AlignRight|Qt::AlignVCenter);
				break;
			default:
				return QVariant(Qt::AlignLeft|Qt::AlignVCenter);
		}
	}
	return QVariant();
}

QVariant
CTxSchedule::headerData ( int section, Qt::Orientation orientation, int role) const
{
	if(role != Qt::DisplayRole)
		return QVariant();
	if(orientation != Qt::Horizontal)
		return QVariant();
	switch(section)
	{
		case 0: return tr("Station Name"); break;
		case 1: return tr("Time [UTC]"); break;
		case 2: return tr("Frequency [kHz]"); break;
		case 3: return tr("Power [kW]"); break;
		case 4: return tr("Country"); break;
		case 5: return tr("Site"); break;
		case 6: return tr("Target"); break;
		case 7: return tr("Language"); break;
		case 8: return tr("Days"); break;
	}
	return "";
}

void
CTxSchedule::update()
{
	/* Get system time */
	time_t ltime;
	time(&ltime);
	// change the active state
	for(size_t i=0; i<ScheduleTable.size(); i++)
	{
		const CScheduleItem& item = ScheduleTable[i];
		CScheduleItem::State newstate = CScheduleItem::IS_INACTIVE;
		if (item.IsActive(ltime, iSecondsPreview) == true)
		{
			/* Check if the station soon will be inactive */
			if (item.IsActive(ltime + NUM_SECONDS_SOON_INACTIVE, iSecondsPreview) == true)
				newstate = CScheduleItem::IS_ACTIVE;
			else
				newstate = CScheduleItem::IS_SOON_INACTIVE;
		}
		else
		{
			/* Station is not active, check preview condition */
			if (iSecondsPreview > 0)
			{
				if (item.IsActive(ltime + iSecondsPreview, iSecondsPreview) == true)
					newstate = CScheduleItem::IS_PREVIEW;
				else
					newstate = CScheduleItem::IS_INACTIVE;
			}
			else
				newstate = CScheduleItem::IS_INACTIVE;
		}
		if(newstate != item.state)
		{
			ScheduleTable[i].state = newstate;
			emit dataChanged(index(i,0),index(i,columnCount()));
		}
	}
}

void
CTxSchedule::load(const string& path)
{
	ScheduleTable.clear();
	/* Empty the string lists for combos filter */

	/* Read initialization file */
	const int	iMaxLenName = 256;
	char		cName[iMaxLenName];
	FILE*		pFile = fopen(path.c_str(), "r");

	/* Open file and init table for stations */
	clear();

	/* Check if opening of file was successful */
	if (pFile == 0)
		return;

	fgets(cName, iMaxLenName, pFile); /* Remove "[DRMSchedule]" */
	if(cName[0] == '[')
		ReadIniFile(pFile);
	else
		ReadCSVFile(pFile);
	fclose(pFile);

	update();

	ListTargets = QStringList("");
	ListCountries = QStringList("");
	ListLanguages = QStringList("");
	QStringList result;

	for(size_t i=0; i<ScheduleTable.size(); i++)
	{
		QString strTarget = QString(ScheduleTable[i].strTarget.c_str());
		QString strCountry = QString(ScheduleTable[i].strCountry.c_str());
		QString strLanguage = QString(ScheduleTable[i].strLanguage.c_str());

		result = ListTargets.filter(strTarget);
		if (result.isEmpty())
			ListTargets.append(strTarget);

		result = ListCountries.filter(strCountry);
		if (result.isEmpty())
			ListCountries.append(strCountry);

		result = ListLanguages.filter(strLanguage);
		if (result.isEmpty())
			ListLanguages.append(strLanguage);
	}

	ListTargets.sort();
	ListCountries.sort();
	ListLanguages.sort();

	reset();
	emit dataChanged ( createIndex(0,0), createIndex(rowCount()-1, columnCount()-1 ));
	emit headerDataChanged(Qt::Horizontal, 0,  columnCount()-1);

}

void CTxSchedule::ReadIniFile(FILE* pFile)
{
	const int	iMaxLenName = 256;
	char		cName[iMaxLenName];
	int			iFileStat;
	bool	    bReadOK = true;

	do
	{
		CScheduleItem StationsItem;

		/* Start stop time */
		int iStartTime, iStopTime;
		iFileStat = fscanf(pFile, "StartStopTimeUTC=%04d-%04d\n",
			&iStartTime, &iStopTime);

		if (iFileStat != 2)
			bReadOK = false;
		else
		{
			StationsItem.SetStartTimeNum(iStartTime);
			StationsItem.SetStopTimeNum(iStopTime);
		}

		/* Days */
		/* Init days with the "irregular" marker in case no valid string could
		   be read */
		string strNewDaysFlags = FLAG_STR_IRREGULAR_TRANSM;

		iFileStat = fscanf(pFile, "Days[SMTWTFS]=%255[^\n|^\r]\n", cName);
		if (iFileStat != 1)
			fscanf(pFile, "\n");
		else
		{
			/* Check for length of input string (must be 7) */
			const string strTMP = cName;
			if (strTMP.length() == 7)
				strNewDaysFlags = strTMP;
		}

		/* Frequency */
		iFileStat = fscanf(pFile, "Frequency=%d\n", &StationsItem.iFreq);
		if (iFileStat != 1)
			bReadOK = false;

		/* Target */
		iFileStat = fscanf(pFile, "Target=%255[^\n|^\r]\n", cName);
		if (iFileStat != 1)
			fscanf(pFile, "\n");
		else
			StationsItem.strTarget = cName;

		/* Power */
		iFileStat = fscanf(pFile, "Power=%255[^\n|^\r]\n", cName);
		if (iFileStat != 1)
			fscanf(pFile, "\n");
		else
			StationsItem.rPower = QString(cName).toFloat();

		/* Name of the station */
		iFileStat = fscanf(pFile, "Programme=%255[^\n|^\r]\n", cName);
		if (iFileStat != 1)
			fscanf(pFile, "\n");
		else
			StationsItem.strName = cName;

		/* Language */
		iFileStat = fscanf(pFile, "Language=%255[^\n|^\r]\n", cName);
		if (iFileStat != 1)
			fscanf(pFile, "\n");
		else
			StationsItem.strLanguage = cName;

		/* Site */
		iFileStat = fscanf(pFile, "Site=%255[^\n|^\r]\n", cName);
		if (iFileStat != 1)
			fscanf(pFile, "\n");
		else
			StationsItem.strSite = cName;

		/* Country */
		iFileStat = fscanf(pFile, "Country=%255[^\n|^\r]\n", cName);
		if (iFileStat != 1)
			fscanf(pFile, "\n");
		else
			StationsItem.strCountry = cName;

		iFileStat = fscanf(pFile, "\n");

		/* Check for error before applying data */
		if (bReadOK == true)
		{
			/* Set "days flag string" and generate strings for displaying active
			   days */
			StationsItem.SetDaysFlagString(strNewDaysFlags);

			/* Add new item in table */
			ScheduleTable.push_back(StationsItem);
		}

	} while (!((iFileStat == EOF) || (bReadOK == false)));
}

void CTxSchedule::ReadCSVFile(FILE* pFile)
{
	const int	iMaxLenRow = 1024;
	char		cRow[iMaxLenRow];
	CStationData data;

	do {
		CScheduleItem StationsItem;

		fgets(cRow, iMaxLenRow, pFile);
		QStringList fields;
		stringstream ss(cRow);
		do {
			string s;
			getline(ss, s, ';');
			fields.push_back(s.c_str());
		} while(!ss.eof());

		StationsItem.iFreq = fields[0].toInt();

		if(fields[1] == "")
		{
			StationsItem.SetStartTimeNum(0);
			StationsItem.SetStopTimeNum(2400);
		}
		else
		{
			QStringList times = fields[1].split("-");
			StationsItem.SetStartTimeNum(times[0].toInt());
			StationsItem.SetStopTimeNum(times[1].toInt());
		}

		if(fields[2].length()>0)
		{
			stringstream ss(fields[2].toStdString());
			char c;
			enum Days { Sunday=0, Monday=1, Tuesday=2, Wednesday=3,
						Thursday=4, Friday=5, Saturday=6 };
			Days first=Sunday, last=Sunday;
			enum { no, in, done } range_state = no;
			// Days[SMTWTFS]=1111111
			string strDays = "0000000";
			while(!ss.eof())
			{
				ss >> c;
				switch(c)
				{
					case '-':
						range_state = in;
						break;
					case 'M':
						ss >> c;
						last = Monday;
						break;
					case 'T':
						ss >> c;
						last = (c=='u')?Tuesday:Thursday;
						break;
					case 'W':
						ss >> c;
						last = Wednesday;
						break;
					case 'F':
						ss >> c;
						last = Friday;
						break;
					case 'S':
						ss >> c;
						last = (c=='u')?Sunday:Saturday;
						break;
				}
				switch(range_state)
				{
					case no:
						strDays[last] = '1';
						break;
					case in:
						first = last;
						range_state = done;
						break;
					case done:
						if(first<last)
						{
							for(int d=first; d<=last; d++)
								strDays[d] = '1';
						}
						range_state = no;
						break;
				}
			}
			StationsItem.SetDaysFlagString(strDays);
		}
		else
			StationsItem.SetDaysFlagString("1111111");

		//StationsItem.rPower = 0.0;
//0   ;1        ;2    ;3  ;4               ;5;6;7;8;9;10
//1170;1600-1700;Mo-Fr;USA;Voice of America;E; ; ;0; ;
		string homecountry;
		if(fields.size()>3)
		{
			homecountry = fields[3].toStdString();
			string c = data.itu_r_country(homecountry);
			if(c == "")
				StationsItem.strCountry = homecountry;
			else
				StationsItem.strCountry = c;
		}

		if(fields.size()>4)
			StationsItem.strName = fields[4].toStdString();

		if(fields.size()>5)
		{
			StationsItem.strLanguage = data.eibi_language(fields[5].toStdString());
		}

		if(fields.size()>6)
		{
			string s = fields[6].toStdString();
			string t = data.eibi_target(s);
			if(t == "")
			{
				string c = data.itu_r_country(s);
				if(c == "")
					StationsItem.strTarget = s;
				else
					StationsItem.strTarget = c;
			}
			else
			{
				StationsItem.strTarget = t;
			}
		}
		string country;
		string stn;
		if(fields.size()>7)
		{
			string s  = StationsItem.strSite = fields[7].toStdString();
			if(s=="") // unknown or main Tx site of the home country
			{
				country = homecountry;
			}
			else
			{
				size_t i=0;
				s += '-';
				if(s[0]=='/') // transmitted from another country
					i++;
				string a,b;
				while(s[i]!='-')
					a += s[i++];
				i++;
				if(i<s.length())
					while(s[i]!='-')
						b += s[i++];
				if(s[0]=='/')
				{
					country = a;
					stn = b;
				}
				else
				{
					if(a.length()==3)
					{
						country = a;
						stn = b;
					}
					else
					{
						country = homecountry;
						stn = a;
					}
				}
			}
		}
		else
		{
			country = homecountry;
		}
		string site = data.eibi_station(country, stn);
		if(site == "")
		{
			//cout << StationsItem.iFreq << " [" << StationsItem.strSite << "] [" << country << "] [" << stn << "]" << endl;
		}
		else
		{
			StationsItem.strSite = site;
		}

		/* Add new item in table */
		ScheduleTable.push_back(StationsItem);

	} while(!feof(pFile));
}

bool CScheduleItem::IsActive(time_t ltime, int iSecondsPreview) const
{
	/* Calculate time in UTC */
	struct tm* gmtCur = gmtime(&ltime);
	const time_t lCurTime = mktime(gmtCur);

	/* Get stop time */
	struct tm* gmtStop = gmtime(&ltime);
	gmtStop->tm_hour = iStopHour;
	gmtStop->tm_min = iStopMinute;
	const time_t lStopTime = mktime(gmtStop);

	/* Get start time */
	struct tm* gmtStart = gmtime(&ltime);
	gmtStart->tm_hour = iStartHour;
	gmtStart->tm_min = iStartMinute;
	const time_t lStartTime = mktime(gmtStart);

	/* Check, if stop time is on next day */
	bool bSecondDay = false;
	if (lStopTime < lStartTime)
	{
		/* Check, if we are at the first or the second day right now */
		if (lCurTime < lStopTime)
		{
			/* Second day. Increase day count */
			gmtCur->tm_wday++;

			/* Check that value is valid (range 0 - 6) */
			if (gmtCur->tm_wday > 6)
				gmtCur->tm_wday = 0;

			/* Set flag */
			bSecondDay = true;
		}
	}

	/* Check day
	   tm_wday: day of week (0 - 6; Sunday = 0). "strDaysFlags" are coded with
	   pseudo binary representation. A one signalls that day is active. The most
	   significant 1 is the sunday, then followed the monday and so on. */
	if ((strDaysFlags[gmtCur->tm_wday] ==
		CHR_ACTIVE_DAY_MARKER) ||
		/* Check also for special case: days are 0000000. This is reserved for
		   DRM test transmissions or irregular transmissions. We define here
		   that these stations are transmitting every day */
		(strDaysFlags == FLAG_STR_IRREGULAR_TRANSM))
	{
		/* Check time interval */
		if (lStopTime > lStartTime)
		{
			if ((lCurTime >= lStartTime) && (lCurTime < lStopTime))
				return true;
		}
		else
		{
			if (bSecondDay == false)
			{
				/* First day. Only check if we are after start time */
				if (lCurTime >= lStartTime)
					return true;
			}
			else
			{
				/* Second day. Only check if we are before stop time */
				if (lCurTime < lStopTime)
					return true;
			}
		}
	}

	return false;
}

void CScheduleItem::SetDaysFlagString(const string strNewDaysFlags)
{
	/* Set internal "days flag" string and "show days" string */
	strDaysFlags = strNewDaysFlags;
	strDaysShow = "";

	/* Init days string vector */
	const QString strDayDef [] =
	{
		QObject::tr("Sun"),
		QObject::tr("Mon"),
		QObject::tr("Tue"),
		QObject::tr("Wed"),
		QObject::tr("Thu"),
		QObject::tr("Fri"),
		QObject::tr("Sat")
	};

	/* First test for day constellations which allow to apply special names */
	if (strDaysFlags == FLAG_STR_IRREGULAR_TRANSM)
		strDaysShow = QObject::tr("irregular");
	else if (strDaysFlags == "1111111")
		strDaysShow = QObject::tr("daily");
	else if (strDaysFlags == "1111100")
		strDaysShow = QObject::tr("Sun to Thu");
	else if (strDaysFlags == "1111110")
		strDaysShow = QObject::tr("Sun to Fri");
	else if (strDaysFlags == "0111110")
		strDaysShow = QObject::tr("weekdays");
	else if (strDaysFlags == "1000001")
		strDaysShow = QObject::tr("weekends");
	else if (strDaysFlags == "0111111")
		strDaysShow = QObject::tr("Mon to Sat");
	else
	{
		/* No special name could be applied, just list all active days */
		QString sep = "";
		for (int i = 0; i < 7; i++)
		{
			/* Check if day is active */
			if (strDaysFlags[i] == CHR_ACTIVE_DAY_MARKER)
			{
				/* Add current day */
				strDaysShow += sep + strDayDef[i];
				sep = ", ";
			}
		}
	}
}
