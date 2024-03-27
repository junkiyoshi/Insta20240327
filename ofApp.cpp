#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetLineWidth(0.25);
	ofEnableDepthTest();
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

	auto ico_sphere = ofIcoSpherePrimitive(250, 4);
	this->base_mesh = ico_sphere.getMesh();
	this->draw_mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
	this->draw_mesh.clear();
	
	for (int k = 0; k < 2; k++) {

		auto noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));

		ofColor color;
		color.setHsb(ofMap(k, 0, 2, 0, 255), 200, 255);

		for (auto v : this->base_mesh.getVertices()) {

			for (int i = 0; i < 16; i++) {

				auto rotation_x = glm::rotate(glm::mat4(), ofMap(ofNoise(glm::vec4(v * 0.006, noise_seed.x + ofGetFrameNum() * 0.025)), 0, 1, -15, 15) * (float)DEG_TO_RAD, glm::vec3(1, 0, 0));
				auto rotation_y = glm::rotate(glm::mat4(), ofMap(ofNoise(glm::vec4(v * 0.006, noise_seed.y + ofGetFrameNum() * 0.025)), 0, 1, -15, 15) * (float)DEG_TO_RAD, glm::vec3(0, 1, 0));
				auto rotation_z = glm::rotate(glm::mat4(), ofMap(ofNoise(glm::vec4(v * 0.006, noise_seed.z + ofGetFrameNum() * 0.025)), 0, 1, -15, 15) * (float)DEG_TO_RAD, glm::vec3(0, 0, 1));

				v = glm::vec4(v, 0) * rotation_z * rotation_y * rotation_x;

				this->draw_mesh.addVertex(v);
				this->draw_mesh.addColor(color);

				if (i > 0) {

					this->draw_mesh.addIndex(this->draw_mesh.getNumVertices() - 1);
					this->draw_mesh.addIndex(this->draw_mesh.getNumVertices() - 2);
				}
			}
		}

		for (auto& v : this->draw_mesh.getVertices()) {

			v.z = 0;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	this->draw_mesh.draw();

	this->cam.end();

	/*
	int start = 50;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}