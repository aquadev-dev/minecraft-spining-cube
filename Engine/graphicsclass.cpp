////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"
#include <d3d11_1.h>
#include "DDSTextureLoader.h"

using namespace DirectX;



GraphicsClass::GraphicsClass()
{
	m_Input = 0;
	m_D3D = 0;
	m_Timer = 0;
	m_ShaderManager = 0;
	m_Position = 0;
	m_Camera = 0;
	m_Model1 = 0;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(HINSTANCE hinstance, HWND hwnd, int screenWidth, int screenHeight)
{
	bool result;

	// Create the input object.  The input object will be used to handle reading the keyboard and mouse input from the user.
	m_Input = new InputClass;
	if (!m_Input)
	{
		return false;
	}

	// Initialize the input object.
	result = m_Input->Initialize(hinstance, hwnd, screenWidth, screenHeight);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the input object.", L"Error", MB_OK);
		return false;
	}

	// Create the Direct3D object.
	m_D3D = new D3DClass;
	if(!m_D3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_D3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// Create the shader manager object.
	m_ShaderManager = new ShaderManagerClass;
	if(!m_ShaderManager)
	{
		return false;
	}

	// Initialize the shader manager object.
	result = m_ShaderManager->Initialize(m_D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the shader manager object.", L"Error", MB_OK);
		return false;
	}

	// Create the timer object.
	m_Timer = new TimerClass;
	if (!m_Timer)
	{
		return false;
	}

	// Initialize the timer object.
	result = m_Timer->Initialize();
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the timer object.", L"Error", MB_OK);
		return false;
	}

	// Create the position object.
	m_Position = new PositionClass;
	if (!m_Position)
	{
		return false;
	}

	// Set the initial position and rotation of the viewer.
	m_Position->SetPosition(0.0f, 0.0f, -10.f);
	m_Position->SetRotation(0.0f, 0.0f, 0.0f);

	// Create the camera object.
	m_Camera = new CameraClass;
	if(!m_Camera)
	{
		return false;
	}

	// Create the model object.
	m_Model1 = new ModelClass;
	if(!m_Model1)
	{
		return false;
	}

}


void GraphicsClass::Shutdown()
{

	// Release the model objects.
	if(m_Model1)
	{
		m_Model1->Shutdown();
		delete m_Model1;
		m_Model1 = 0;
	}

	// Release the camera object.
	if(m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Release the position object.
	if (m_Position)
	{
		delete m_Position;
		m_Position = 0;
	}

	// Release the shader manager object.
	if(m_ShaderManager)
	{
		m_ShaderManager->Shutdown();
		delete m_ShaderManager;
		m_ShaderManager = 0;
	}

	// Release the timer object.
	if (m_Timer)
	{
		delete m_Timer;
		m_Timer = 0;
	}

	// Release the D3D object.
	if(m_D3D)
	{
		m_D3D->Shutdown();
		delete m_D3D;
		m_D3D = 0;
	}

	// Release the input object.
	if (m_Input)
	{
		m_Input->Shutdown();
		delete m_Input;
		m_Input = 0;
	}

	return;
}


bool GraphicsClass::Frame()
{
	bool result;
	static float rotation = 0.0f;

	// Update the system stats.
	m_Timer->Frame();

	// Read the user input.
	result = m_Input->Frame();
	if (!result)
	{
		return false;
	}

	// Check if the user pressed escape and wants to exit the application.
	if (m_Input->IsEscapePressed() == true)
	{
		return false;
	}

	// Do the frame input processing.
	result = HandleMovementInput(m_Timer->GetTime());
	if (!result)
	{
		return false;
	}

	// Load the correct texture based on the texture number
	switch (textureNumber)
	{
	case 0: // Cobblestone
		result = m_Model1->Initialize(m_D3D->GetDevice(), L"../Engine/data/cube.txt", L"../Engine/data/Cobblestone.dds");
		if (!result)
		{
			return false;
		}
		break;
	case 1: // Wood Planks
		result = m_Model1->Initialize(m_D3D->GetDevice(), L"../Engine/data/cube.txt", L"../Engine/data/WoodPlanks_.dds");
		if (!result)
		{
			return false;
		}
		break;

	case 2: // Obsidian
		result = m_Model1->Initialize(m_D3D->GetDevice(), L"../Engine/data/cube.txt", L"../Engine/data/Obsidian.dds");
		if (!result)
		{
			return false;
		}
		break;
	case 3: // Diamond Ore
		result = m_Model1->Initialize(m_D3D->GetDevice(), L"../Engine/data/cube.txt", L"../Engine/data/Diamond_Ore.dds");
		if (!result)
		{
			return false;
		}
		break;
	case 4: // Gold Ore
		result = m_Model1->Initialize(m_D3D->GetDevice(), L"../Engine/data/cube.txt", L"../Engine/data/Gold_Ore.dds");
		if (!result)
		{
			return false;
		}
		break;
	case 5: // Emerald Ore
		result = m_Model1->Initialize(m_D3D->GetDevice(), L"../Engine/data/cube.txt", L"../Engine/data/Emerald_Ore.dds");
		if (!result)
		{
			return false;
		}
		break;
	case 6: // Diamond Block
		result = m_Model1->Initialize(m_D3D->GetDevice(), L"../Engine/data/cube.txt", L"../Engine/data/Diamond_Block.dds");
		if (!result)
		{
			return false;
		}
		break;
	case 7: // Gold Block
		result = m_Model1->Initialize(m_D3D->GetDevice(), L"../Engine/data/cube.txt", L"../Engine/data/Gold_Block.dds");
		if (!result)
		{
			return false;
		}
		break;
	case 8: // Emerald Block
		result = m_Model1->Initialize(m_D3D->GetDevice(), L"../Engine/data/cube.txt", L"../Engine/data/Emerald_Block.dds");
		if (!result)
		{
			return false;
		}
		break;
	case 9: // Netherite Block
		result = m_Model1->Initialize(m_D3D->GetDevice(), L"../Engine/data/cube.txt", L"../Engine/data/Block_of_Netherite.dds");
		if (!result)
		{
			return false;
		}
		break;

	default:
		break;
	}

	rotation += (float)XM_PI * 0.005f; // Rotate the cube
	if (rotation > 360.0f) // Reset the rotation if it exceeds 360 degrees
	{
		rotation -= 360.0f;
	}
	// Render the graphics.
	result = Render(rotation);
	if (!result)
	{
		return false;
	}

	return true;
}

bool GraphicsClass::HandleMovementInput(float frameTime)
{
	bool keyDown;
	float posX, posY, posZ, rotX, rotY, rotZ;

	// Set the frame time for calculating the updated position.
	m_Position->SetFrameTime(frameTime);

	// Handle the movement input. (Similar to Minecraft)
	keyDown = m_Input->IsAPressed();
	if (keyDown) m_Position->StrafeLeft(keyDown);

	keyDown = m_Input->IsDPressed();
	if(keyDown) m_Position->StrafeRight(keyDown);

	keyDown = m_Input->IsWPressed();
	if(keyDown) m_Position->MoveForward(keyDown);

	keyDown = m_Input->IsSPressed();
	if (keyDown) m_Position->MoveBackward(keyDown);

	keyDown = m_Input->IsUpPressed();
	if (keyDown) m_Position->MoveUpward(keyDown);

	keyDown = m_Input->IsDownPressed();
	if (keyDown) m_Position->MoveDownward(keyDown);

	// Texture selection using number keys
	
	keyDown = m_Input->Is0Pressed();
	if (keyDown) textureNumber = 0; // Cobblestone

	keyDown = m_Input->Is1Pressed();
	if (keyDown) textureNumber = 1; // Wood Planks

	keyDown = m_Input->Is2Pressed();
	if (keyDown) textureNumber = 2; // Obsidian

	keyDown = m_Input->Is3Pressed();
	if (keyDown) textureNumber = 3; // Diamond Ore

	keyDown = m_Input->Is4Pressed();
	if (keyDown) textureNumber = 4; // Gold Ore

	keyDown = m_Input->Is5Pressed();
	if (keyDown) textureNumber = 5; // Emerald Ore

	keyDown = m_Input->Is6Pressed();
	if (keyDown) textureNumber = 6; // Diamond Block

	keyDown = m_Input->Is7Pressed();
	if (keyDown) textureNumber = 7; // Gold Block
	
	keyDown = m_Input->Is8Pressed();
	if (keyDown) textureNumber = 8; // Emerald Block

	keyDown = m_Input->Is9Pressed();
	if (keyDown) textureNumber = 9; // Netherite Block

	
	// HandleMouse Rotations
	m_Position->MouseRotate(m_Input->GetMouseX(), m_Input->GetMouseY());

	// Get the view point position/rotation.
	m_Position->GetPosition(posX, posY, posZ);
	m_Position->GetRotation(rotX, rotY, rotZ);

	// Set the position of the camera.
	m_Camera->SetPosition(posX, posY, posZ);
	m_Camera->SetRotation(rotX, rotY, rotZ);

	m_Input->ResetCursorPos();

	return true;
}

bool GraphicsClass::Render(float rotation)
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, translateMatrix;
	XMFLOAT3 cameraPosition; 
	bool result;

	// Clear the buffers to begin the scene.
	m_D3D->BeginScene(0.2f, 0.2f, 0.2f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	// Get the world, view, and projection matrices from the camera and d3d objects.
	m_D3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_D3D->GetProjectionMatrix(projectionMatrix);


	


	//Render models in scene
	
	// Setup the rotation and translation of the first model.
	//worldMatrix = XMMatrixRotationZ(rotation * 3.0f);
	translateMatrix = XMMatrixTranslation(0.0f, 0.0f, 0.0f);
	worldMatrix = XMMatrixMultiply(worldMatrix, translateMatrix);

	// Set the rotation factors
	// worldMatrix = XMMatrixRotationY(rotation);

	XMVECTOR MyAxis;
	MyAxis = XMVectorSet(0.0f, 1.0f, 0.0f, 1.0f);

	worldMatrix = XMMatrixMultiply(worldMatrix, XMMatrixRotationAxis(MyAxis, rotation));

	m_D3D->EnableDepth();

	//Render the first model using the texture shader.
	m_Model1->Render(m_D3D->GetDeviceContext());
	result = m_ShaderManager->RenderTextureShader(m_D3D->GetDeviceContext(), m_Model1->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, 
												  m_Model1->GetTexture());
	if(!result)
	{
		return false;
	}

	

	// Present the rendered scene to the screen.
	m_D3D->EndScene();

	return true;
}