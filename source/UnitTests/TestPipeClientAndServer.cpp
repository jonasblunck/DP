#include "stdafx.h"
#include <pipeClient.h>
#include <pipeServer.h>
#include "PipesTestClass.h"

#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(TestPipes)
{
	PipesTestClass pipes;

	TEST_CLASS_INITIALIZE(Initialise)
	{

	}  

	TEST_METHOD(Pipes_ServerInConnectModeCanDisconnect)
	{			
		PipeServer server(&pipes);

		Assert::IsTrue(server.InitializeServerSide(0x989));
		server.Disconnect();
	}

	TEST_METHOD(Pipes_ClientCanConnectToServerAndDisconnect)
	{		
		PipeServer server(&pipes);
		PipeClient client;

		server.InitializeServerSide(0x11);
		Assert::IsTrue(client.Connect(0x11));
    
		client.Disconnect();
		server.Disconnect();
	}

	TEST_METHOD(Pipes_ClientCanSendDataToServer_Client_SentMessage)
	{
		PipesTestClass pipes;
		PipeServer server(&pipes);
		PipeClient client;

		char message[] = "the message..";
		pipes.m_len = 0;

		server.InitializeServerSide(GetCurrentProcessId());
		client.Connect(GetCurrentProcessId());
		Assert::IsTrue(client.Send((BYTE*)message, sizeof(message)));
    
		client.Disconnect();
		server.Disconnect();
	}

	// Wait messages being returned are incorrect - possibly returning on another event
	/*
	TEST_METHOD(Pipes_ClientCanSendDataToServer_Client_Waits)
	{
		PipesTestClass pipes;
		PipeServer server(&pipes);
		PipeClient client;

		char message[] = "the message..";
		pipes.m_len = 0;

		server.InitializeServerSide(GetCurrentProcessId());
		client.Connect(GetCurrentProcessId());
		client.Send((BYTE*)message, sizeof(message));

		Sleep(1000);

		Assert::AreEqual(WAIT_OBJECT_0, WaitForSingleObject(pipes.m_dataEvent, INFINITE));	 

		client.Disconnect();
		server.Disconnect();
	}*/

	TEST_METHOD(Pipes_ClientCanSendDataToServer_Message_LenGreaterThanZero)
	{
		PipesTestClass pipes;
		PipeServer server(&pipes);
		PipeClient client;

		char message[] = "the message..";
		pipes.m_len = 0;

		server.InitializeServerSide(GetCurrentProcessId());
		client.Connect(GetCurrentProcessId());
		client.Send((BYTE*)message, sizeof(message));

		Sleep(1000);

		WaitForSingleObject(pipes.m_dataEvent, 500);
		Assert::IsTrue(pipes.m_len > 0);	  

		client.Disconnect();
		server.Disconnect();
	}

	TEST_METHOD(Pipes_ClientCanSendDataToServer_Message_HasValue)
	{
		PipesTestClass pipes;
		PipeServer server(&pipes);
		PipeClient client;

		char message[] = "the message..";
		pipes.m_len = 0;

		server.InitializeServerSide(GetCurrentProcessId());
		client.Connect(GetCurrentProcessId());
		client.Send((BYTE*)message, sizeof(message));

		WaitForSingleObject(pipes.m_dataEvent, 500);	  
		Assert::AreEqual(0, memcmp(pipes.m_data, message, pipes.m_len));    // we received what was sent?

		client.Disconnect();
		server.Disconnect();
	}
 
	// Wait messages being returned are incorrect - possibly returning on another event
	/*
	TEST_METHOD(Pipes_ClientCanReconnectAfterDisconnect_Client_Waits)
	{
		PipesTestClass pipes;
		PipeServer server(&pipes);
		PipeClient client;

		server.InitializeServerSide(GetCurrentProcessId());
		client.Connect(GetCurrentProcessId());
		client.Disconnect();

		PipeClient client2;

		client2.Connect(GetCurrentProcessId());

		char message[] = "the text..";
		client2.Send((BYTE*)message, sizeof(message));

		Sleep(1000);

		Assert::AreEqual(WAIT_OBJECT_0, WaitForSingleObject(pipes.m_dataEvent, INFINITE));		
	}*/

	TEST_METHOD(Pipes_ClientCanReconnectAfterDisconnect_Message_HasValue)
	{
		PipesTestClass pipes;
		PipeServer server(&pipes);
		PipeClient client;

		server.InitializeServerSide(GetCurrentProcessId());
		client.Connect(GetCurrentProcessId());
		client.Disconnect();

		PipeClient client2;

		client2.Connect(GetCurrentProcessId());

		char message[] = "the text..";
		client2.Send((BYTE*)message, sizeof(message));

		Sleep(1000);

		WaitForSingleObject(pipes.m_dataEvent, INFINITE);

		Assert::AreEqual(0, memcmp(pipes.m_data, message, pipes.m_len));

		client2.Disconnect();
		server.Disconnect();
	}
	
	TEST_METHOD(Pipes_ClientConnectsLaterThanServerStarts_Message_LenGreaterThanZero)
	{
		PipesTestClass pipes;
		PipeServer server(&pipes);
		PipeClient client;

		char message[] = "the message..";
		pipes.m_len = 0;

		server.InitializeServerSide(0x8877);
		client.Connect(0x8877);
		client.Send((BYTE*)message, sizeof(message));

		Sleep(1000);

		WaitForSingleObject(pipes.m_dataEvent, 100);

		Assert::IsTrue(pipes.m_len > 0);		

		client.Disconnect();
		server.Disconnect();
	}

	TEST_METHOD(Pipes_ClientConnectsLaterThanServerStarts_Message_HasValue)
	{
		PipesTestClass pipes;
		PipeServer server(&pipes);
		PipeClient client;

		char message[] = "the message..";
		pipes.m_len = 0;

		server.InitializeServerSide(0x8877);
		client.Connect(0x8877);
		client.Send((BYTE*)message, sizeof(message));
		WaitForSingleObject(pipes.m_dataEvent, 100);
	
		Assert::AreEqual(0, memcmp(pipes.m_data, message, pipes.m_len));

		client.Disconnect();
		server.Disconnect();
	}
	
	TEST_METHOD(Pipes_ClientConnectsLaterThanServerStarts_Message_IsReceived)
	{
		PipesTestClass pipes;
		PipeServer server(&pipes);
		PipeClient client;

		char message[] = "the message..";
		pipes.m_len = 0;

		server.InitializeServerSide(0x8877);
		client.Connect(0x8877);
		client.Send((BYTE*)message, sizeof(message));
		WaitForSingleObject(pipes.m_dataEvent, 100);

		Assert::AreEqual(0, memcmp(pipes.m_data, message, pipes.m_len));

		client.Disconnect();
		server.Disconnect();
	}

	TEST_METHOD(Pipes_ServerCanSendResponse_Message_CanRead)
	{
		PipesTestClass pipes;
		PipeServer server(&pipes);
		PipeClient client;

		char message[] = "The quick brown fox jumps over the lazy dog.";
		BYTE buffer[256];
		DWORD len = 0;

		server.InitializeServerSide(0xdead);
		client.Connect(0xdead);
		server.Send((BYTE*)message, sizeof(message));

		Assert::IsTrue(client.Read(buffer, sizeof(buffer), &len));

		client.Disconnect();
		server.Disconnect();
	}

	TEST_METHOD(Pipes_ServerCanSendResponse_Message_LenGreaterThanZero)
	{
		PipesTestClass pipes;
		PipeServer server(&pipes);
		PipeClient client;

		char message[] = "The quick brown fox jumps over the lazy dog.";
		BYTE buffer[256];
		DWORD len = 0;

		server.InitializeServerSide(0xdead);
		client.Connect(0xdead);
		server.Send((BYTE*)message, sizeof(message));
		client.Read(buffer, sizeof(buffer), &len);

		Assert::IsTrue(len > 0);		

		client.Disconnect();
		server.Disconnect();
	}

	TEST_METHOD(Pipes_ServerCanSendResponse_Message_HasValue)
	{
		PipesTestClass pipes;
		PipeServer server(&pipes);
		PipeClient client;

		char message[] = "The quick brown fox jumps over the lazy dog.";
		BYTE buffer[256];
		DWORD len = 0;

		server.InitializeServerSide(0xdead);
		client.Connect(0xdead);
		server.Send((BYTE*)message, sizeof(message));
		client.Read(buffer, sizeof(buffer), &len);

		Assert::AreEqual(0, memcmp(buffer, message, len));

		client.Disconnect();
		server.Disconnect();
	}

	TEST_METHOD_INITIALIZE(InitialiseMethod)
	{
		pipes.m_dataEvent = ::CreateEvent(NULL, FALSE, FALSE, NULL);
	}

	TEST_METHOD_CLEANUP(CleanupMethod)
	{
		CloseHandle(pipes.m_dataEvent);	
	}
};
