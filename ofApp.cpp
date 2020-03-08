#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}
//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->frame.clear();

	int len = 100;

	for (int r = 0; r < 6; r++) {

		vector<glm::vec3> vertices;
		vertices.push_back(glm::vec3());
		vertices.push_back(glm::vec3(-len * 0.5, -len * 0.5, -len * 0.5));
		vertices.push_back(glm::vec3(len * 0.5, -len * 0.5, -len * 0.5));
		vertices.push_back(glm::vec3(len * 0.5, -len * 0.5, len * 0.5));
		vertices.push_back(glm::vec3(-len * 0.5, -len * 0.5, len * 0.5));
	
		int angle;
		glm::highp_mat4 rotation;
		float noise_value;
		if (r < 4) {
			angle = r * 90;
			rotation = glm::rotate(glm::mat4(), (float)(angle * DEG_TO_RAD), glm::vec3(1, 0, 0));
			noise_value = ofNoise(ofRandom(1000), ofGetFrameNum() * 0.01);

		}
		else {

			angle = r == 5 ? 90 : 270;
			rotation = glm::rotate(glm::mat4(), (float)(angle * DEG_TO_RAD), glm::vec3(0, 0, 1));
			noise_value = ofNoise(ofRandom(1000), ofGetFrameNum() * 0.01);
		}

		auto rotation_y = glm::rotate(glm::mat4(), (float)(noise_value < 0.55 ? 0 : ofMap(noise_value, 0.55, 1, 0, 12)), glm::vec3(0, 1, 0));
		for (auto& vertex : vertices) { 

			vertex = (glm::vec4(vertex, 0) + glm::vec4(0, noise_value < 0.48 ? -1 : ofMap(noise_value, 0.48, 1, -1, -150), 0, 0)) * rotation_y * rotation;
		}

		auto index = this->face.getNumVertices();
		this->face.addVertices(vertices);
		this->frame.addVertices(vertices);

		this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index + 2);
		this->face.addIndex(index + 0); this->face.addIndex(index + 2); this->face.addIndex(index + 3);
		this->face.addIndex(index + 0); this->face.addIndex(index + 3); this->face.addIndex(index + 4);
		this->face.addIndex(index + 0); this->face.addIndex(index + 4); this->face.addIndex(index + 1);

		this->face.addIndex(index + 1); this->face.addIndex(index + 2); this->face.addIndex(index + 3);
		this->face.addIndex(index + 1); this->face.addIndex(index + 3); this->face.addIndex(index + 4);

		this->frame.addIndex(index + 0); this->frame.addIndex(index + 1);
		this->frame.addIndex(index + 0); this->frame.addIndex(index + 2);
		this->frame.addIndex(index + 0); this->frame.addIndex(index + 3);
		this->frame.addIndex(index + 0); this->frame.addIndex(index + 4);

		this->frame.addIndex(index + 1); this->frame.addIndex(index + 2);
		this->frame.addIndex(index + 2); this->frame.addIndex(index + 3);
		this->frame.addIndex(index + 3); this->frame.addIndex(index + 4);
		this->frame.addIndex(index + 4); this->frame.addIndex(index + 1);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.85);
	ofRotateX(ofGetFrameNum() * 0.5);

	ofSetColor(39);
	this->face.draw();

	ofSetColor(239);
	this->frame.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}