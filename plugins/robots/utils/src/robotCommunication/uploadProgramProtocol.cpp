/* Copyright 2016 CyberTech Labs Ltd., Yurii Litvinov
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License. */

#include "utils/robotCommunication/uploadProgramProtocol.h"

#include <QtCore/QState>
#include <QtCore/QFileInfo>

#include "utils/robotCommunication/tcpRobotCommunicator.h"
#include "protocol.h"

using namespace utils::robotCommunication;

UploadProgramProtocol::UploadProgramProtocol(TcpRobotCommunicator &communicator)
	: mProtocol(new Protocol(communicator))
	, mWaitingForUploadingComplete(new QState())
{
	mProtocol->addSuccessTransition(mWaitingForUploadingComplete, &TcpRobotCommunicator::uploadProgramDone);
	mProtocol->addErrorTransition(mWaitingForUploadingComplete, &TcpRobotCommunicator::uploadProgramError);

	connect(mProtocol.data(), &Protocol::success, this, &UploadProgramProtocol::success);
	connect(mProtocol.data(), &Protocol::error, this, &UploadProgramProtocol::error);
	connect(mProtocol.data(), &Protocol::timeout, this, &UploadProgramProtocol::timeout);
}

UploadProgramProtocol::~UploadProgramProtocol()
{
}

void UploadProgramProtocol::run(const QFileInfo &programToUpload)
{
	mProtocol->setAction(mWaitingForUploadingComplete
			, [programToUpload](TcpRobotCommunicatorInterface &communicator) {
					communicator.uploadProgram(programToUpload.canonicalFilePath());
	});

	mProtocol->run();
}
