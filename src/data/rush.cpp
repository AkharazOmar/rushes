/****************************************************************************
 *
 * Rushes! is a video cataloger application based on QtAv, OpenCV and FFMpeg.
 * Copyright (C) 2017 Remy Ruttner
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

#include "rush.h"
#include "extract.h"

#include <QFileInfo>
#include <QDateTime>

Rush::Rush()
    : QObject()
{
    database_id = -1;

    // os data
    file_name = QString();
    thumbnail_file_name = QString();
    utc_creation_time = 0;

    // user data
    rating = -1;

    // video data
    length = -1; // mseconds
    width = -1;
    height = -1;
    fps = -1;
    bitrate = -1; // Kb/s
    video_codec = QString();

    // audio data
    audio_codec = QString();
    sample_rate = -1; // Hz
    channel = QString();
    audio_bitrate = -1; // kb/s
}

Rush::Rush(const Rush &other)
    : QObject()
{
    *this = other;
}

Rush &Rush::operator=(const Rush &other)
{
    this->database_id = other.database_id;
    this->file_name = other.file_name;
    this->thumbnail_file_name = other.thumbnail_file_name;
    this->utc_creation_time = other.utc_creation_time;
    this->rating = other.rating;
    this->length = other.length;
    this->width = other.width;
    this->height = other.height;
    this->fps = other.fps;
    this->bitrate = other.bitrate;
    this->video_codec = other.video_codec;
    this->audio_codec = other.audio_codec;
    this->sample_rate = other.sample_rate;
    this->channel = other.channel;
    this->audio_bitrate = other.audio_bitrate;

    return *this;
}

QHash<QString, Rush*> Rush::m_rush_cache = QHash<QString, Rush*>();

Rush *Rush::getRush(const QString& file_name)
{
    if (m_rush_cache.contains(file_name))
        return m_rush_cache[file_name];

    Rush *rush = new Rush();
    rush->file_name = file_name;

    QFileInfo file_info(rush->file_name);
    if (file_info.isFile())
        rush->utc_creation_time = qMin(file_info.created().toSecsSinceEpoch(), file_info.lastModified().toSecsSinceEpoch());

    m_rush_cache[file_name] = rush;
    return rush;
}

Extract *Rush::extract()
{
    Extract* extract = new Extract(this);
    return extract;
}

bool Rush::hasMetadata()
{
    return (width != -1 && fps != -1 && length != -1);
}

bool Rush::isInDatabase()
{
    return database_id >= 0;
}
