//#include <default/Window.h>
//
//Window::Window(int width, int height, std::string title, Camera* camera)
//{
//	lastX = width / 2.0f;
//	lastY = height / 2.0f;
//	firstMouse = true;
//	traced = false;
//	deltaTime = 0.0f;
//	lastFrame = 0.0f;
//
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//	GLFWwindow* window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
//	if (window == NULL)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//	}
//	glfwMakeContextCurrent(window);
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		std::cout << "Failed to initialize GLAD" << std::endl;
//	}
//	glfwSetInputMode(glWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
//	glfwSetCursorPosCallback(window, mouseCallback);
//	glfwSetScrollCallback(window, scrollCallback);
//}
//
//void Window::addWorld(World* world)
//{
//	this->world = world;
//}
//
//void Window::addChunkController(ChunkController* cc)
//{
//	this->cc = cc;
//}
//
//void Window::processInput()
//{
//	if (glfwGetKey(glWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
//		glfwSetWindowShouldClose(glWindow, true);
//	}
//	const float cameraSpeed = 2.5f * deltaTime; // adjust accordingly
//	if (glfwGetKey(glWindow, GLFW_KEY_W) == GLFW_PRESS)
//		camera->ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
//	if (glfwGetKey(glWindow, GLFW_KEY_S) == GLFW_PRESS)
//		camera->ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
//	if (glfwGetKey(glWindow, GLFW_KEY_A) == GLFW_PRESS)
//		camera->ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
//	if (glfwGetKey(glWindow, GLFW_KEY_D) == GLFW_PRESS)
//		camera->ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);
//	if (glfwGetKey(glWindow, GLFW_KEY_R) == GLFW_PRESS)
//		cc->updateChunk(world->getChunkWorldPosition().x, 0, world->getChunkWorldPosition().z);
//	if (glfwGetKey(glWindow, GLFW_KEY_T) == GLFW_PRESS && !traced) {
//		/*for (int i = 1; i < (int)DISTANCE / STEPSIZE; i++) {
//			glm::vec3 step = (camera.Position + (camera.Front * ((float)i * STEPSIZE)));
//			std::vector<float> linevert{ camera.Position.x , camera.Position.y , camera.Position.z, step.x, step.y, step.z };
//
//			lines.insert(lines.end(), new Line(linevert, 2));
//		}*/
//		glm::vec3 trace = LineTrace::trace(camera->Position, camera->Front, cc);
//		traced = true;
//
//		//std::cout << trace.x << ", " << trace.y << ", " << trace.z << std::endl;
//	}
//	if (glfwGetKey(glWindow, GLFW_KEY_T) == GLFW_RELEASE && traced) {
//		traced = false;
//	}
//
//	void mouseCallback(GLFWwindow * window, double xposIn, double yposIn)
//	{
//		float xpos = static_cast<float>(xposIn);
//		float ypos = static_cast<float>(yposIn);
//
//		if (firstMouse)
//		{
//			lastX = xpos;
//			lastY = ypos;
//			firstMouse = false;
//		}
//
//		float xoffset = xpos - lastX;
//		float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
//
//		lastX = xpos;
//		lastY = ypos;
//
//		camera->ProcessMouseMovement(xoffset, yoffset);
//	}
//
//	void scrollCallback(GLFWwindow * window, double xoffset, double yoffset)
//	{
//		camera->ProcessMouseScroll(static_cast<float>(yoffset));
//	}
//}
//