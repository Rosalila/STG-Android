#include "RosalilaGraphics/RosalilaGraphics.h"

static void checkGlError(const char* op) {
    for (GLint error = glGetError(); error; error
            = glGetError()) {
__android_log_print(ANDROID_LOG_DEBUG, "CHUUUY", "after %s() glError (0x%x)\n", op, error);
    }
}

RosalilaGraphics::RosalilaGraphics()
{
//	this->screen_width=1920;
//	this->screen_height=1080;

	this->screen_width=1280;
	this->screen_height=720;

	int ortho_width = 1920;
	int ortho_height = 1080;

//	int ortho_width = 1280;
//	int ortho_height = 720;

	camera_x=camera_y=0;

    // Initialize SDL
        if(SDL_Init(SDL_INIT_VIDEO) < 0)
                exit(0);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);

        // Open the window where we will draw
        window = SDL_CreateWindow("OpenGL Test",
                           SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                           screen_width, screen_height, SDL_WINDOW_OPENGL|SDL_WINDOW_SHOWN);

    // Create the OpenGL context for the window we just opened
    context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, context);
    // Configure SDL for OpenGL or GLES 1.1
    SDL_GL_SetSwapInterval(0); // 1 = use vertical synchronisation (vsync)
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 0);//24 default?


	//testa de sof
	glDisable(GL_DITHER);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_FASTEST);
	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);


    // Configure OpenGL propre
    glClearColor(0, 0, 0, 255);
    glEnable(GL_TEXTURE_2D);
    glViewport(0, 0, ortho_width, ortho_height);
    glMatrixMode(GL_PROJECTION);
    glOrtho(0, screen_width, screen_height, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);




    //Fps cap
    frames_per_seccond = 60;
    frame = 0;
    fps=new Timer();
    update=new Timer();
    fps->start();
    update->start();

	//effects
	this->transparency_effect=255;

	iterations=0;

/*
    char *archivo=new char[255];
    strcpy(archivo,"config.xml");
    TiXmlDocument doc_t( archivo );
    doc_t.LoadFile();
    TiXmlDocument *doc;
    doc=&doc_t;

    TiXmlNode *config_file=doc->FirstChild("ConfigFile");

    TiXmlElement *screensize_element=config_file->FirstChild("Resolution")->ToElement();
    screen_width=atoi(screensize_element->Attribute("x"));
    screen_height=atoi(screensize_element->Attribute("y"));

    TiXmlElement *resolution_element=config_file->FirstChild("ScreenSize")->ToElement();
    int screen_resized_width=atoi(resolution_element->Attribute("x"));
    int screen_resized_height=atoi(resolution_element->Attribute("y"));

    TiXmlElement *fullscreen_element=config_file->FirstChild("Fullscreen")->ToElement();
    fullscreen=strcmp(fullscreen_element->Attribute("enabled"),"yes")==0;


    TiXmlElement *font_element=config_file->FirstChild("Font")->ToElement();

    int font_size=10;
    if(font_element->Attribute("size")!=NULL)
    {
        font_size=atoi(font_element->Attribute("size"));
    }
    int font_red=0;
    if(font_element->Attribute("red")!=NULL)
    {
        font_red=atoi(font_element->Attribute("red"));
    }
    int font_green=0;
    if(font_element->Attribute("green")!=NULL)
    {
        font_green=atoi(font_element->Attribute("green"));
    }
    int font_blue=0;
    if(font_element->Attribute("blue")!=NULL)
    {
        font_blue=atoi(font_element->Attribute("blue"));
    }

    //Internal initializations
    screen=NULL;
    joystick_1 = NULL;
    joystick_2 = NULL;

    screen_bpp = 32;
    camera_x=camera_y=0;

    //Initialize all SDL subsystems
    if( SDL_Init( SDL_INIT_EVERYTHING | SDL_INIT_AUDIO | SDL_INIT_VIDEO ) == -1 )
    {
        writeLogLine(SDL_GetError());
        return;
    }
*/

/*
    //Initialize SDL_ttf
    if( TTF_Init() == -1 )
    {
        writeLogLine(SDL_GetError());
        return;
    }
*/
/*
    font = NULL;
    textColor.r = font_red;
    textColor.g = font_green;
    textColor.b = font_blue;


    font = TTF_OpenFont( "misc/font.ttf", font_size );

    if(font==NULL)
    {
        writeLogLine("Could not init font. Place it on /misc/font.ttf .");
    }


    SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 ); // *new*
*/
    //Set up the screen
/*
    if(!fullscreen)
        screen = SDL_SetVideoMode( screen_resized_width, screen_resized_height, screen_bpp, SDL_OPENGL );
    else
        screen = SDL_SetVideoMode( 0, 0, screen_bpp, SDL_OPENGL | SDL_FULLSCREEN );


    //Set the openGL state?
    glEnable( GL_TEXTURE_2D );
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

    glViewport( 0, 0, screen->w, screen->h );

    glClear( GL_COLOR_BUFFER_BIT );

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
*/

/*
    glOrtho(0.0f, screen_width, screen_height, 0.0f, -1.0f, 1.0f);


    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();



    //If there was an error in setting up the screen
    if( screen == NULL )
    {
        writeLogLine("Error: Could not initialize SDL screen.");
        return;
    }
*/
    //Set the window caption
/*
    SDL_WM_SetCaption( "Rosalila fighter engine", NULL );


    //Init joysticks
    if( SDL_NumJoysticks() == 1 )
    {
        writeLogLine("1 joystick was found.");
        joystick_1 = SDL_JoystickOpen( 0 );
        if(joystick_1 != NULL)
            writeLogLine("Joystick for player 1 initialized succesfully.");
        else
            writeLogLine("Error initializing joystick for player 1.");
    }
    if( SDL_NumJoysticks() == 2 )
    {
        writeLogLine("2 joysticks were found.");
        joystick_1 = SDL_JoystickOpen( 0 );
        if(joystick_1 != NULL)
            writeLogLine("Joystick for player 1 initialized succesfully.");
        else
            writeLogLine("Error initializing joystick for player 1.");
        joystick_2 = SDL_JoystickOpen( 1 );
        if(joystick_2 != NULL)
            writeLogLine("Joystick for player 2 initialized succesfully.");
        else
            writeLogLine("Error initializing joystick for player 2.");
    }

    //If everything initialized fine
    writeLogLine("Success! SDL initialized.");
    return;
*/
}

void RosalilaGraphics::resetScreen()
{
//    //Set up the screen
//    if(!fullscreen)
//        screen = SDL_SetVideoMode( screen_resized_width, screen_resized_height, screen_bpp, SDL_OPENGL );
//    else
//        screen = SDL_SetVideoMode( screen_resized_width, screen_resized_height, screen_bpp, SDL_OPENGL | SDL_FULLSCREEN );
}

RosalilaGraphics::~RosalilaGraphics()
{
    //Free the surface
    SDL_FreeSurface( screen );

    //Quit SDL
    SDL_Quit();
}


Image* RosalilaGraphics::getTexture(std::string filename)
{
__android_log_print(ANDROID_LOG_DEBUG, "YYYY", "gettan %s",filename.c_str());	

	GLuint texture;

    // Local variables for extracting properties about the image
    GLuint n_colours = 0;
    GLenum format = (GLenum) NULL;

    // Load the image using SDL_image
        SDL_Surface* surface = IMG_Load(filename.c_str());
        if(!surface)
        return 0;
 
    // Make sure the image length and width are powers of 2
//    if (!ISPWR2(surface->w) || !ISPWR2(surface->h))
//        return 0;

        //get number of channels in the SDL surface
    n_colours = surface->format->BytesPerPixel;
    switch(n_colours)
    {
        case 3: format = GL_RGB; break;
        case 4: format = GL_RGBA; break;
        default: return 0; break;
    }

    // Request an OpenGL texture handle
    glGenTextures(1, &texture);
 
    // Bind the texture object to the current block
    glBindTexture(GL_TEXTURE_2D, texture);
 
    // Set the texture’s properties
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, format, surface->w, surface->h, 0,
                    format, GL_UNSIGNED_BYTE, surface->pixels);

    Image*image=new Image();
    image->setTexture(texture);
    image->setWidth(surface->w);
    image->setHeight(surface->h);

    // The original bitmap is no longer needed
        SDL_FreeSurface(surface);

__android_log_print(ANDROID_LOG_DEBUG, "UUUUU", "success gettan %s",filename.c_str());	
	return image;

}

void RosalilaGraphics::draw2DImage	(
             Image* image,
             int size_x,int size_y,
             int position_x,int position_y,
             float scale,
             float rotation,
             bool flipHorizontally,
             int depth_effect_x,
             int depth_effect_y,
             Color color_effects,
             bool camera_align)
{
	glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    //Camera and depth effect
    if(depth_effect_x>0)
    {
        position_x-=camera_x/depth_effect_x;
    }else if(depth_effect_x<0)
    {
        position_x-=camera_x*-depth_effect_x;
    }else if(camera_align)
    {
        position_x-=camera_x;
    }

    if(depth_effect_y>0)
    {
        position_y+=camera_y/depth_effect_y;
    }else if(depth_effect_y<0)
    {
        position_y+=camera_y*-depth_effect_y;
    }else if(camera_align)
    {
        position_y+=camera_y;
    }

    // Set up position, rotation, colour
    glTranslatef(position_x+size_x/2, position_y+size_y/2, 0.0);
	//glTranslatef(position_x+size_x/2, position_y+size_y/2, 0.0);
	//glTranslatef(0, 0, 0.0);
    glRotatef(-rotation, 0.0, 0.0, 1.0);
 
    // Bind the texture to which subsequent calls refer to
    glBindTexture(GL_TEXTURE_2D, image->texture);

glColor4f(color_effects.getRed()/255.0f, color_effects.getGreen()/255.0f, color_effects.getBlue()/255.0f,color_effects.getAlpha()/255.0f);
 
    // Start drawing texture
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        GLfloat size[18], coords[12];
    glVertexPointer(3, GL_FLOAT, 0, size);
        glTexCoordPointer(2, GL_FLOAT, 0, coords);


// Top-left triangle
		size[0]=-size_x/2;
		size[1]=-size_y/2;
		size[2]=0;

		size[3]=size_x/2;
		size[4]=-size_y/2;
		size[5]=0;

		size[6]=size_x/2;
		size[7]=size_y/2;
		size[8]=0;

		coords[0]=0;
		coords[1]=0;

		coords[2]=1;
		coords[3]=0;

		coords[4]=1;
		coords[5]=1;

//triangle 2
		size[9]=-size_x/2;
		size[10]=-size_y/2;
		size[11]=0;

		size[12]=-size_x/2;
		size[13]=size_y/2;
		size[14]=0;

		size[15]=size_x/2;
		size[16]=size_y/2;
		size[17]=0;
        //size = {-16,-16,0, -16,16,0, 16,16,0}; ///FIXME
		coords[6]=0;
		coords[7]=0;

		coords[8]=0;
		coords[9]=1;

		coords[10]=1;
		coords[11]=1;

        glDrawArrays(GL_TRIANGLES, 0, 6);
 
    // Stop drawing texture
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
 
    // Reset back to the origin
    glLoadIdentity();
}


void RosalilaGraphics::draw2DImage	(
             Image* image,
             int size_x,int size_y,
             int position_x,int position_y,
             float scale,
             float rotation,
             bool flipHorizontally,
             int depth_effect_x,
             int depth_effect_y,
             Color color_effects,
             bool camera_align,
             bool allow_alpha)
{
	if(allow_alpha)
		glEnable(GL_BLEND);
	else
		glDisable(GL_BLEND);

    glEnable(GL_TEXTURE_2D);
    //Camera and depth effect
    if(depth_effect_x>0)
    {
        position_x-=camera_x/depth_effect_x;
    }else if(depth_effect_x<0)
    {
        position_x-=camera_x*-depth_effect_x;
    }else if(camera_align)
    {
        position_x-=camera_x;
    }

    if(depth_effect_y>0)
    {
        position_y+=camera_y/depth_effect_y;
    }else if(depth_effect_y<0)
    {
        position_y+=camera_y*-depth_effect_y;
    }else if(camera_align)
    {
        position_y+=camera_y;
    }

    // Set up position, rotation, colour
    glTranslatef(position_x+size_x/2, position_y+size_y/2, 0.0);
	//glTranslatef(position_x+size_x/2, position_y+size_y/2, 0.0);
	//glTranslatef(0, 0, 0.0);
    glRotatef(-rotation, 0.0, 0.0, 1.0);

    // Bind the texture to which subsequent calls refer to
    glBindTexture(GL_TEXTURE_2D, image->texture);

glColor4f(color_effects.getRed()/255.0f, color_effects.getGreen()/255.0f, color_effects.getBlue()/255.0f,color_effects.getAlpha()/255.0f);

    // Start drawing texture
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        GLfloat size[18], coords[12];
    glVertexPointer(3, GL_FLOAT, 0, size);
        glTexCoordPointer(2, GL_FLOAT, 0, coords);


// Top-left triangle
		size[0]=-size_x/2;
		size[1]=-size_y/2;
		size[2]=0;

		size[3]=size_x/2;
		size[4]=-size_y/2;
		size[5]=0;

		size[6]=size_x/2;
		size[7]=size_y/2;
		size[8]=0;

		coords[0]=0;
		coords[1]=0;

		coords[2]=1;
		coords[3]=0;

		coords[4]=1;
		coords[5]=1;

//triangle 2
		size[9]=-size_x/2;
		size[10]=-size_y/2;
		size[11]=0;

		size[12]=-size_x/2;
		size[13]=size_y/2;
		size[14]=0;

		size[15]=size_x/2;
		size[16]=size_y/2;
		size[17]=0;
        //size = {-16,-16,0, -16,16,0, 16,16,0}; ///FIXME
		coords[6]=0;
		coords[7]=0;

		coords[8]=0;
		coords[9]=1;

		coords[10]=1;
		coords[11]=1;

        glDrawArrays(GL_TRIANGLES, 0, 6);

    // Stop drawing texture
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    // Reset back to the origin
    glLoadIdentity();
}

void RosalilaGraphics::draw2DImageBatch(
             Image* image,
			 int size_x,int size_y,
			 vector<int> position_x,vector<int> position_y,
			 float scale,
			 vector<float> rotation,
			 bool flipHorizontally,
			 int depth_effect_x,
			 int depth_effect_y,
			 Color color_effects,
			 bool camera_align)
{
	glEnable(GL_TEXTURE_2D);
	// Set up position, rotation, colour
	//glTranslatef(position_x[i]+size_x/2, position_y[i]+size_y/2, 0.0);
	glTranslatef(0, 0, 0.0);
	//glTranslatef(position_x+size_x/2, position_y+size_y/2, 0.0);
	//glTranslatef(0, 0, 0.0);
	//glRotatef(-rotation[i], 0.0, 0.0, 1.0);
	glRotatef(0.0, 0.0, 0.0, 1.0);

	// Bind the texture to which subsequent calls refer to
	glBindTexture(GL_TEXTURE_2D, image->texture);

	glColor4f(color_effects.getRed()/255.0f, color_effects.getGreen()/255.0f, color_effects.getBlue()/255.0f,color_effects.getAlpha()/255.0f);

	// Start drawing texture
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		GLfloat size[18*position_x.size()], coords[12*position_x.size()];
	glVertexPointer(3, GL_FLOAT, 0, size);
		glTexCoordPointer(2, GL_FLOAT, 0, coords);


	for(int i=0;i<position_x.size();i++)
	{
		//Camera and depth effect
		if(depth_effect_x>0)
		{
			position_x[i]-=camera_x/depth_effect_x;
		}else if(depth_effect_x<0)
		{
			position_x[i]-=camera_x*-depth_effect_x;
		}else if(camera_align)
		{
			position_x[i]-=camera_x;
		}

		if(depth_effect_y>0)
		{
			position_y[i]+=camera_y/depth_effect_y;
		}else if(depth_effect_y<0)
		{
			position_y[i]+=camera_y*-depth_effect_y;
		}else if(camera_align)
		{
			position_y[i]+=camera_y;
		}

		double pos_x_align=position_x[i]+size_x/2;
		double pos_y_align=position_y[i]+size_y/2;
		double size_x_quart=size_x/2;
		double size_y_quart=size_y/2;
		double base_angle = atan (size_y_quart/size_x_quart) * 180.0 / PI;
		double hypo = sqrt(pow(((float)size_x)/2.0f,2.0f)+pow(((float)size_y)/2.0f,2.0f));

		double centerX=pos_x_align;
		double point2x=size_x_quart;
		double centerY=pos_y_align;
		double point2y=size_y_quart;
		double x=-rotation[i]*PI/180;

		//centerX + (point2x)*cos(x* 180.0 / PI) - (point2y)*sin(x* 180.0 / PI);

		double v_1_x=centerX + (-point2x)*cos(x) - (-point2y)*sin(x);
		double v_1_y=centerY + (-point2x)*sin(x) + (-point2y)*cos(x);

		double v_2_x=centerX + (point2x)*cos(x) - (-point2y)*sin(x);
		double v_2_y=centerY + (point2x)*sin(x) + (-point2y)*cos(x);

		double v_3_x=centerX + (point2x)*cos(x) - (point2y)*sin(x);
		double v_3_y=centerY + (point2x)*sin(x) + (point2y)*cos(x);

		double v_4_x=centerX + (-point2x)*cos(x) - (point2y)*sin(x);
		double v_4_y=centerY + (-point2x)*sin(x) + (point2y)*cos(x);



		int current_size_offset=i*18;
		int current_coord_offset=i*12;
		// Top-right triangle

				size[0+current_size_offset]=v_1_x;
				size[1+current_size_offset]=v_1_y;
				size[2+current_size_offset]=0;


				size[3+current_size_offset]=v_2_x;
				size[4+current_size_offset]=v_2_y;
				size[5+current_size_offset]=0;

				size[6+current_size_offset]=v_3_x;
				size[7+current_size_offset]=v_3_y;
				size[8+current_size_offset]=0;

				coords[0+current_coord_offset]=0;
				coords[1+current_coord_offset]=0;

				coords[2+current_coord_offset]=1;
				coords[3+current_coord_offset]=0;

				coords[4+current_coord_offset]=1;
				coords[5+current_coord_offset]=1;

		// Bot-left triangle
				size[9+current_size_offset]=v_1_x;
				size[10+current_size_offset]=v_1_y;
				size[11+current_size_offset]=0;

				size[12+current_size_offset]=v_4_x;
				size[13+current_size_offset]=v_4_y;
				size[14+current_size_offset]=0;

				size[15+current_size_offset]=v_3_x;
				size[16+current_size_offset]=v_3_y;
				size[17+current_size_offset]=0;
				//size = {-16,-16,0, -16,16,0, 16,16,0}; ///FIXME
				coords[6+current_coord_offset]=0;
				coords[7+current_coord_offset]=0;

				coords[8+current_coord_offset]=0;
				coords[9+current_coord_offset]=1;

				coords[10+current_coord_offset]=1;
				coords[11+current_coord_offset]=1;

	}

	glDrawArrays(GL_TRIANGLES, 0, 6*position_x.size());

	// Stop drawing texture
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	// Reset back to the origin
	glLoadIdentity();
}

void RosalilaGraphics::drawRectangle(int x,int y,int width,int height,float rotation,int red,int green,int blue,int alpha,bool camera_align)
{
    glDisable(GL_TEXTURE_2D);

    if(camera_align)
    {
        y+=camera_y;
        x-=camera_x;
    }

	glTranslatef(x, y, 0.0);
	glRotatef(-rotation, 0.0, 0.0, 1.0);

    GLfloat rect[] = {
        0, height,
        width, height, 
        width, 0,
        0, 0
    };
	glEnableClientState(GL_VERTEX_ARRAY);
    glColor4f((float)(red/255.0f),(float)(green/255.0f),(float)(blue/255.0f),(float)(alpha/255.0f));
    glVertexPointer(2, GL_FLOAT, 0, rect);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glLoadIdentity();
}

void RosalilaGraphics::frameCap()
{
    // Clear the entire screen
    //glClear(GL_COLOR_BUFFER_BIT);

    frame++;

    //If a second has passed since the caption was last updated

    //If we want to cap the frame rate
    if(update->get_ticks() < 1000 / frames_per_seccond)
    {
        //Sleep the remaining frame time
        SDL_Delay( ( 1000 / frames_per_seccond ) - update->get_ticks() );
    }

    std::string caption;

    //Calculate the frames per second and create the string
    //caption = "Average Frames Per Second: " + toString(frame / ( fps->get_ticks() / 1000.f ));

    iterations++;
    if(iterations%10==0)
    	__android_log_print(ANDROID_LOG_DEBUG, "FPS", "FPS: %i\n", (int)(frame / ( fps->get_ticks() / 1000.f)) );



    //Reset the caption
/*
    SDL_WM_SetCaption( caption.c_str(), NULL );
*/
    // Flip the buffers to update the screen
    //Restart the update timer
    update->start();
}

void RosalilaGraphics::drawText(std::string text,int position_x,int position_y)
{
/*
    if(text=="")
        text=" ";
    GLuint texture;

    SDL_Surface *message = NULL;
//    message = TTF_RenderUTF8_Blended( font, text.c_str(), textColor );


    // Prepare the texture for the font
    GLenum textFormat;
    if(message->format->BytesPerPixel == 4)
    {
        // alpha
        if(message->format->Rmask == 0x000000ff)
            textFormat = GL_RGBA;
        else
            textFormat = GL_BGRA_EXT;
    }

    // Create the font's texture
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, message->format->BytesPerPixel, message->w, message->h, 0, textFormat, GL_UNSIGNED_BYTE, message->pixels);

    GLfloat x1=0.f+position_x;
    GLfloat y1=0.f+position_y;
    GLfloat x2=0.f+position_x+message->w;
    GLfloat y2=0.f+position_y+message->h;
    SDL_FreeSurface(message);


    //OpenGL draw
    glBindTexture( GL_TEXTURE_2D, texture );
    glColor3ub(255, 255, 255);
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
    glBegin( GL_QUADS );

        //Bottom-left vertex (corner)
        glTexCoord2i( 0, 0 );
        glVertex3f( x1, y1, 0.0f );

        //Bottom-right vertex (corner)
        glTexCoord2i( 1, 0 );
        glVertex3f( x2, y1, 0.f );

        //Top-right vertex (corner)
        glTexCoord2i( 1, 1 );
        glVertex3f( x2, y2, 0.f );

        //Top-left vertex (corner)
        glTexCoord2i( 0, 1 );
        glVertex3f( x1, y2, 0.f );

    glEnd();
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_2D);
*/
}

void RosalilaGraphics::draw3D()
{
/*
    //Explosion
    for (std::list<Explosion*>::iterator explosion = explosions.begin(); explosion != explosions.end(); explosion++)
        ((Explosion*)*explosion)->render(this->screen_width,this->screen_height);


    std::list<Explosion*>::iterator i = explosions.begin();
    while (i != explosions.end())
    {
        Explosion*e=(Explosion*)*i;
        if (e->iteration>e->duration)
        {
            explosions.erase(i++);
            delete e;
        }
        else
        {
            ++i;
        }
    }

//    //Explosion2
//    for (std::list<Explosion2*>::iterator explosion2 = explosions2.begin(); explosion2 != explosions2.end(); explosion2++)
//        ((Explosion2*)*explosion2)->render(this->screen_width,this->screen_height);

    std::list<Explosion2*>::iterator i2 = explosions2.begin();
    while (i2 != explosions2.end())
    {
        Explosion2*e=(Explosion2*)*i2;
        if (e->iteration>e->duration)
        {
            explosions2.erase(i2++);
            delete e;
        }
        else
        {
            ++i2;
        }
    }
*/
}

void RosalilaGraphics::addExplosion(int x,int y)
{
/*
    explosions.push_back(new Explosion(x-camera_x,y-camera_y));
    explosions2.push_back(new Explosion2(x-camera_x,y-camera_y));
*/
}

void RosalilaGraphics::draw3DCube(int x,int y,float size,Color color)
{
/*
    glDisable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();

//    gluPerspective (45.0, (GLfloat) screen_width / (GLfloat) screen_height, 0.1, 100.0);

    glMatrixMode (GL_MODELVIEW);

    glEnable (GL_LIGHT0);
    glEnable (GL_LIGHT1);
    glLightfv (GL_LIGHT0, GL_AMBIENT, cube.light0Amb);
    glLightfv (GL_LIGHT0, GL_DIFFUSE, cube.light0Dif);
    glLightfv (GL_LIGHT0, GL_SPECULAR, cube.light0Spec);
    glLightfv (GL_LIGHT0, GL_POSITION, cube.light0Pos);

    glLightfv (GL_LIGHT1, GL_AMBIENT, cube.light1Amb);
    glLightfv (GL_LIGHT1, GL_DIFFUSE, cube.light1Dif);
    glLightfv (GL_LIGHT1, GL_SPECULAR, cube.light1Spec);
    glLightfv (GL_LIGHT1, GL_POSITION, cube.light1Pos);

    glLightModelf (GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
    glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT, cube.materialAmb);
    glMaterialfv (GL_FRONT_AND_BACK, GL_DIFFUSE, cube.materialDif);
    glMaterialfv (GL_FRONT_AND_BACK, GL_SPECULAR, cube.materialSpec);
    glMaterialf (GL_FRONT_AND_BACK, GL_SHININESS, cube.materialShininess);
    glEnable (GL_NORMALIZE);

    cube.logic();


    //glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity ();

    //Place the camera
    //
    glPushMatrix ();
    float pos_x=x;
    float pos_y=y;
    //camera align
    pos_x-=camera_x;
    pos_y+=camera_y;

    pos_x+=695.0;
    pos_y+=393.0;
    glTranslatef (-((screen_width-pos_x)/9.25), ((screen_height-pos_y)/9.25), -100.0);
    glRotatef (cube.angle, 0.0, 1.0, 0.0);
    cube.setMaterialColor(color.getRed(),color.getGreen(),color.getBlue(),color.getAlpha());

    //Draw
    glEnable (GL_LIGHTING);
    glDisable (GL_LIGHT0);
    glEnable (GL_DEPTH_TEST);

//    glutSolidCube (size);

    glDisable (GL_LIGHTING);

    glPopMatrix();
*/
}

void RosalilaGraphics::drawObject()
{
/*
    Object3D object;
    object.draw();
*/
}

void RosalilaGraphics::explode(float pos_x,float pos_y)
{
//    explosion.newExplosion(pos_x,pos_y);
}

void RosalilaGraphics::updateScreen()
{
    //Write errors to the log
    std::string error= ">>>";
    error+=SDL_GetError();
    if(error!=">>>")
        writeLogLine(error);


	if(isSlowActive())
	{
		transparency_effect-=7;
	}else
	{
		transparency_effect+=7;
	}

	if(transparency_effect>255)
		transparency_effect=255;

	if(isSlowActive()
		&& getReceiver()->isOuyaDown('m') && getReceiver()->isOuyaDown('s'))
	{
		if(transparency_effect<128)
		{
			transparency_effect=128;
		}
	}else if(transparency_effect<192)
	{
		transparency_effect=192;
	}

    //Draw
    //frameCap();

    // Flip the buffers to update the screen
    SDL_GL_SwapWindow(window);
	//glClear(GL_COLOR_BUFFER_BIT);
	checkGlError("checking glError");
}

void RosalilaGraphics::video(RosalilaGraphics*painter)
{
//    // Surface for the movie
//    SDL_Surface *movieSurface = 0;
//
//    // Holds the movie information
//    SMPEG_Info movieInfo;
//
//    // Load the movie
//    SMPEG *movie =  0;
//
//    painter->screen = SDL_SetVideoMode(painter->screen_resized_width, painter->screen_resized_height, painter->screen_bpp,SDL_HWSURFACE | SDL_DOUBLEBUF | SDL_ANYFORMAT);
//
//    // Load the movie and store the information about it
//    movie = SMPEG_new("demo.mpg", &movieInfo, true);
//
//    char* error = SMPEG_error(movie);
//
//    if( error != NULL || movie == NULL )
//    {
//        printf( "Error loading MPEG: %s\n", error );
//        return;
//    }
//
//    // Create a temporary surface to render the movie to
//    SDL_Surface *tempSurface2 = SDL_CreateRGBSurface(SDL_SWSURFACE,
//    movieInfo.width, movieInfo.height, 32, painter->screen->format->Rmask,
//    painter->screen->format->Gmask, painter->screen->format->Bmask, painter->screen->format->Amask);
//
//    // Now make a surface optimized for the main screen
//    movieSurface = SDL_DisplayFormat(tempSurface2);
//
//    // Free the temporary surface
//    SDL_FreeSurface(tempSurface2);
//
//    // Set the surface to draw to
//    SMPEG_setdisplay(movie, movieSurface, 0, 0);
//
//    // Set the display region
//    SMPEG_setdisplayregion(movie, 0, 0, movieInfo.width, movieInfo.height);
//
//    // Loop forever
//    SMPEG_loop(movie, -1);
//
//    SDL_ShowCursor(SDL_DISABLE);
//
//    int done = 0;
//
//    SMPEG_play(movie);
//    SMPEG_getinfo(movie, &movieInfo);
//
//    while(done == 0)
//    {
//        SDL_Event event;
//
//        while (SDL_PollEvent(&event))
//        {
//            if (event.type == SDL_QUIT)
//            {
//                done = 1;
//            }
//
//            if (event.type == SDL_KEYDOWN)
//            {
//                if (event.key.keysym.sym == SDLK_ESCAPE)
//                {
//                    done = 1;
//                }
//            }
//        }
//
//        SDL_Rect dest;
//        dest.x = 0;
//        dest.y = 0;
//        SDL_BlitSurface(movieSurface, NULL, painter->screen, &dest);
//
//        // Flip the main screen
//        SDL_Flip(painter->screen);
//    }
//
//    SDL_FreeSurface(movieSurface);
//    SMPEG_stop(movie);
//    SMPEG_delete(movie);
//    movie = NULL;
//    SDL_ShowCursor(SDL_ENABLE);
//    painter->resetScreen();
}
void RosalilaGraphics::resetFpsCount()
{
	fps->reset();
	fps->start();
	frame=0;
}
