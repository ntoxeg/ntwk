/*
 *  Author: Jacky Alcine <jacky.alcine@thesii.org>
 *
 *  Copyright 2011 (c) Wintermute Developers
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 */

#include "wntrntwk.hpp"
#include <boost/python.hpp>

using namespace boost::python;
using namespace Wintermute;
using namespace Wintermute::Network;

namespace Wintermute {
    namespace Network {
        BOOST_PYTHON_MODULE(wntrntwk){
            class_<Message>("Message",init<const string, QVariant*>())
                    .def("hasProperty",&Message::hasProperty)
                    .def("setProperty",&Message::setProperty)
                    /// @todo Fix this issue; since we've defined a non-const & const method; I think this won't expose properly. Consider just using the method to be exposed for C?
                    //.def("getProperty",&Message::getProperty)
                    .def("getMessageType",&Message::getMessageType)
                    .def("getCreationTime",&Message::getCreationTime)
                    .def("toString",&Message::toString);

            class_<BroadcastMessage, bases<Message> >("BroadcastMessage",init<const BroadcastType>())
                    .def("getBroadcastType",&BroadcastMessage::getBroadcastType);

            class_<Broadcast>("Broadcast",no_init)
                    .def("initialize",&Broadcast::initialize)
                    .def("isActive",&Broadcast::isActive)
                    .def("destroy",&Broadcast::destroy);
        }

    }
}
