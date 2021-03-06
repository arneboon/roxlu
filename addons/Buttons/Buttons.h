#ifndef RUIH
#define RUIH

#include <vector>


#include "ofMain.h"

#include "Shader.h"
#include "VertexData.h"
#include "BitmapFont.h"
#include "Text.h"
#include "VAO.h"
#include "Error.h"

#include "Types.h"
#include "Element.h"
#include "Slider.h"
#include "Toggle.h"
#include "Button.h"
#include "Storage.h"

using std::vector;
using namespace roxlu;

const string BUTTONS_VS = " \
	uniform mat4 projection_matrix; \
	attribute vec4 pos; \
	attribute vec4 col; \
	varying vec4 vcol; \
	void main() { \
		vcol = col; \
		gl_Position = projection_matrix * pos; \
	} \
";


const string BUTTONS_FS = "  \
	varying vec4 vcol; \
	void main() { \
		gl_FragColor = vcol; \
	}\
";


namespace buttons {

struct ElementByName {
	ElementByName(const string& name)
		:name(name)
	{
	}
	
	bool operator()(const Element* el) {
		return el->name == name;
	}
	string name;
};

class Buttons {
public:
	Buttons(const string& title, int w);
	~Buttons();
	
	void update();
	void draw();
	void debugDraw();
	
	void save();
	void save(const string& file);
	void load();
	void load(const string& file);
	
	Sliderf& addFloat(const string& label, float& value);
	Slideri& addInt(const string& label, int& value);
	Toggle& addBool(const string& label, bool& value);

	template<class T>
	Button<T>& addButton(const std::string& label, int id,  T* cb) {
		buttons::Button<T>* el = new Button<T>(id, cb, createCleanName(label));
		addElement(el, label);
		return *el;
	}
	
	void createOrtho(float w, float h);
	int getElementsHeight();
	int getPanelHeight();
	int getPanelWidth();
		
	// must be called from your app
	void onMouseMoved(int x, int y);
	void onMouseDown(int x, int y);
	void onMouseUp(int x, int y);
	void onResize(int newW, int newH);
	
	void setPosition(int x, int y);
	friend class Storage; 
	Element* getElement(const string& name);
		
private:
	void addElement(Element* el, const string& label);
	void onMouseEnter(int x, int y);
	void onMouseLeave(int x, int y);
	void onMouseDragged(int dx, int dy);

	void generateVertices();
	void generatePanelVertices();
	void generateElementVertices(); // create vertices for panel
	void updateDynamicTexts();
	void updateStaticTextPositions();
	void positionElements();
	void flagChanged();
	string createCleanName(const string& ugly);
	
	vector<Element*> elements;
		
	int x; // TODO: do we create a generic "interactive object" ? 
	int y;
	int w; 
	int h;
	int win_w;
	int win_h;
	float header_color_top[4];	
	float header_color_bottom[4];
	float shadow_color[4];
	int header_h;
	int border;
	int state;
	bool is_changed;
	bool is_mouse_inside;
	bool triggered_drag;
	int mdx; // drag x
	int mdy; // drag y
	int pmx; // prev mouse x
	int pmy; // prev mouse y;
	string title;
	int title_dx; // static text index
	ButtonVertices vd;
	int num_panel_vertices; // number of vertices used by the panel itself
	
	bool is_mouse_down;
	static bool shaders_initialized;
	
	static BitmapFont* bmf;
	Text* static_text;
	Text* dynamic_text;
	static Shader gui_shader;
	
	
	float ortho[16];
	//float model[16];

	VAO vao;
	GLuint vbo;
	bool first_run;
};

inline void Buttons::flagChanged() {
	is_changed = true;
}

inline string Buttons::createCleanName(const string& ugly) {
	string clean_name;
	for(int i = 0; i < ugly.size(); ++i) {
		if(isalnum(ugly[i])) {
			clean_name.push_back(tolower(ugly[i]));
		}
	}
	return clean_name;
}

} // buttons

#endif