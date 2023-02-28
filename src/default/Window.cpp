#include <default/Window.h>

Window::Window(int width, int height, std::string title, Player* player, World* world, ChunkController* cc)
{
	this->width = width;
	this->height = height;
	this->title = title;
	lastX = width / 2.0f;
	lastY = height / 2.0f;
	firstMouse = true;
	traced = false;
	detailedTraced = false;
	jumped = false;
	deltaTime = 0.0f;
	lastFrame = 0.0f;

	this->player = player;
	this->world = world;
	this->cc = cc;
}

void Window::start()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glWindow = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (glWindow == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
	}
	glfwMakeContextCurrent(glWindow);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
	glfwSetInputMode(glWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	Window::setWindow(this);
	glfwMaximizeWindow(glWindow);
	glfwSetCursorPosCallback(glWindow, Window::staticMouseCallback);
	glfwSetScrollCallback(glWindow, Window::staticScrollCallback);
}

void Window::processInput(Player* player)
{
	
	if (glfwGetKey(glWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(glWindow, true);
	}
	const float cameraSpeed = 2.5f * deltaTime; // adjust accordingly
	if (glfwGetKey(glWindow, GLFW_KEY_W) == GLFW_PRESS) 
		player->camera->ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
	if (glfwGetKey(glWindow, GLFW_KEY_S) == GLFW_PRESS)
		player->camera->ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
	if (glfwGetKey(glWindow, GLFW_KEY_A) == GLFW_PRESS)
		player->camera->ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
	if (glfwGetKey(glWindow, GLFW_KEY_D) == GLFW_PRESS)
		player->camera->ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);
	if (glfwGetKey(glWindow, GLFW_KEY_E) == GLFW_PRESS && !invCycledUp) {
		player->inventory->cycleSelection(1);
		invCycledUp = true;
	}
	if (glfwGetKey(glWindow, GLFW_KEY_Q) == GLFW_PRESS && !invCycledDown) {
		player->inventory->cycleSelection(-1);
		invCycledDown = true;
	}
	if (glfwGetKey(glWindow, GLFW_KEY_E) == GLFW_RELEASE && invCycledUp) 
		invCycledUp = false;
	if (glfwGetKey(glWindow, GLFW_KEY_Q) == GLFW_RELEASE && invCycledDown) 
		invCycledDown = false;
	if (glfwGetKey(glWindow, GLFW_KEY_R) == GLFW_PRESS && !spawnItem) {
		player->dropItem(world, cc->getMeshBuilder());
		spawnItem = true;
	}
	if (glfwGetKey(glWindow, GLFW_KEY_R) == GLFW_RELEASE && spawnItem) {
		spawnItem = false;
	}

	if (jetpack) {
		if (glfwGetKey(glWindow, GLFW_KEY_SPACE) == GLFW_PRESS && !jumped) {
			player->jump();
			jumped = true;
		}
		if (glfwGetKey(glWindow, GLFW_KEY_SPACE) == GLFW_RELEASE && jumped) {
			jumped = false;
		}
	}
	else {
		if (glfwGetKey(glWindow, GLFW_KEY_SPACE) == GLFW_PRESS) {
			player->jump();
		}
	}

	if (glfwGetKey(glWindow, GLFW_KEY_F) == GLFW_PRESS && !jetpackToggle) {
		jetpack = !jetpack;
		player->gravity = jetpack;
		jetpackToggle = true;
	}
	if (glfwGetKey(glWindow, GLFW_KEY_F) == GLFW_RELEASE && jetpackToggle) {
		jetpackToggle = false;
	}

	if (glfwGetMouseButton(glWindow, GLFW_MOUSE_BUTTON_1) == GLFW_PRESS && !traced) {
		/*for (int i = 1; i < (int)DISTANCE / STEPSIZE; i++) {
			glm::vec3 step = (camera.Position + (camera.Front * ((float)i * STEPSIZE)));
			std::vector<float> linevert{ camera.Position.x , camera.Position.y , camera.Position.z, step.x, step.y, step.z };

			lines.insert(lines.end(), new Line(linevert, 2));
		}*/
		BlockType trace = LineTrace::remove(player->camera->Position, player->camera->Front, cc);
		if (trace != BlockType::NOTHING) {
			std::cout << tge::getBlockName(trace) << std::endl;
			player->inventory->addItem(trace);
		}
		traced = true;

		//std::cout << trace.x << ", " << trace.y << ", " << trace.z << std::endl;
	}
	if (glfwGetMouseButton(glWindow, GLFW_MOUSE_BUTTON_1) == GLFW_RELEASE && traced) {
		traced = false;
	}
	if (glfwGetMouseButton(glWindow, GLFW_MOUSE_BUTTON_2) == GLFW_PRESS && !detailedTraced) {
		glm::vec3 trace = LineTrace::create(player->camera->Position, player->camera->Front, cc, player);
		detailedTraced = true;

		//std::cout << trace.x << ", " << trace.y << ", " << trace.z << std::endl;
	}
	if (glfwGetMouseButton(glWindow, GLFW_MOUSE_BUTTON_2) == GLFW_RELEASE && detailedTraced) {
		detailedTraced = false;
	}
	
	if (glfwGetKey(glWindow, GLFW_KEY_W) != GLFW_PRESS && glfwGetKey(glWindow, GLFW_KEY_S) != GLFW_PRESS) 
	{
		player->camera->ProcessKeyboard(Camera_Movement::NO_FORWARDBACK, deltaTime);
	}

	if (glfwGetKey(glWindow, GLFW_KEY_A) != GLFW_PRESS && glfwGetKey(glWindow, GLFW_KEY_D) != GLFW_PRESS)
	{
		player->camera->ProcessKeyboard(Camera_Movement::NO_RIGHTLEFT, deltaTime);
	}


		
}

void Window::mouseCallback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	player->camera->ProcessMouseMovement(xoffset, yoffset);
}

void Window::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	player->inventory->cycleSelection(static_cast<int>(yoffset));

}

void Window::updateDeltaTime()
{
	float currentFrame = (float)glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;
}

float Window::getDeltaTime()
{
	return deltaTime;
}

void Window::staticMouseCallback(GLFWwindow* window, double xposIn, double yposIn)
{
	sWindow->mouseCallback(window, xposIn, yposIn);
}

void Window::staticScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	sWindow->scrollCallback(window, xoffset, yoffset);
}


void Window::setWindow(Window* window)
{
	Window::sWindow = window;
}

Window* Window::sWindow = nullptr;


