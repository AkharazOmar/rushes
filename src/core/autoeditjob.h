/****************************************************************************
 *
 * Rushes! is a video cataloger application based on QtAv, OpenCV and FFMpeg.
 * Copyright (C) 2018 Remy Ruttner
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 ****************************************************************************/
#ifndef AUTOEDITJOB_H
#define AUTOEDITJOB_H

#include "core/jobsmaster.h"

#include "data/extract.h"

class AutoEditJob : public Job
{
    Q_OBJECT

public:
    AutoEditJob(const QString &xml_output_file_name, QList<Extract*> extracts, const QString& music_file_name, bool prores_export = false);

    void run();

private:
    QList<Extract*> m_extracts;
    QString m_music_file_name;
    QString m_xml_output_file_name;
    bool m_prores_export;
};

#endif // AUTOEDITJOB_H
