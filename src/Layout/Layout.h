#pragma once

class Layout{

    Layout();

    ~Layout();

    void handleToolBar(float& toolbarHeight);

    void handleInspectorTab(float toolbarHeight, float projectTabHeight, float hierarchyTabWidth, float& inspectorTabWidth);

    void handleScene(float toolbarHeight, float projectTabHeight, float hierarchyTabWidth, float& inspectorTabWidth);

    void handleHierarchyTab(float toolbarHeight, float projectTabHeight, float& hierarchyTabWidth);
    
    void handleProjectTab(float toolbarHeight, float& projectTabHeight); 
};


