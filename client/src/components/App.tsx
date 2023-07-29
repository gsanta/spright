import React, { useCallback, useEffect, useMemo, useState } from 'react';
import { Tab, TabList, TabPanel, TabPanels, Tabs } from '@chakra-ui/react';
import './app.scss';
import Layout from './layout/Layout';
import Box from './box/Box';
import Split from 'react-split';
import Canvas from '../features/canvas/Canvas';
import useInitApp from '../features/canvas/hooks/useInitApp';
import LayerPanel from '../features/layer/ui/components/LayerPanel';
import ToolOptionsPanel from '@/features/tool/tool_options/ui/ToolOptionsPanel';
import SceneViewer from '@/features/scene_viewer/SceneViewer';
import KeyboardHandler from '@/features/keyboard/KeyboardHandler';
import { editor } from '@/features/editor/Editor';
import Header from './header/Header';
import ToolEventListener from '@/features/tool/toolbar/ToolEventListener';
import Toolbar from '@/features/tool/toolbar/ui/Toolbar';

const App = () => {
  const [canvasNode, setCanvasNode] = useState<HTMLCanvasElement>();

  const canvasRef = useCallback((node: HTMLCanvasElement) => {
    if (node) {
      Module.canvas = node;
      setCanvasNode(node);
    }
  }, []);

  const app = useMemo(
    () => ({
      editorApi: editor,
      editorEvents: window.EditorEvents,
      keyboardHandler: new KeyboardHandler(),
    }),
    [],
  );

  useInitApp(canvasNode);

  useEffect(() => {
    const toolEventListener = new ToolEventListener(app.editorApi);
    toolEventListener.listen(window.EditorEvents);

    /* code to prevent emscripten compiled code from eating key input */
    window.addEventListener(
      'keydown',
      function (event) {
        app.keyboardHandler.emitKeyDown(event);
        event.stopImmediatePropagation();
      },
      true,
    );

    window.addEventListener(
      'keyup',
      function (event) {
        event.stopImmediatePropagation();
      },
      true,
    );
    // eslint-disable-next-line react-hooks/exhaustive-deps
  }, []);

  return (
    <Layout header={<Header />} footer={<Box bgColor="orange.400" height="40px"></Box>}>
      <Box width="50px">
        <Toolbar />
      </Box>
      <Split className="split" direction="horizontal" sizes={[75, 25]}>
        <Canvas ref={canvasRef} />
        <Split className="split-vertical" direction="vertical" sizes={[50, 50]}>
          <Box overflowY="auto">
            <LayerPanel />
          </Box>
          <Tabs display="flex" flexDir="column" isLazy>
            <TabList>
              <Tab>Options</Tab>
              <Tab>3D Viewer</Tab>
            </TabList>
            <TabPanels alignItems="stretch" display="flex" flex="1">
              <TabPanel flex="1">
                <ToolOptionsPanel />
              </TabPanel>
              <TabPanel display="flex" flex="1">
                <SceneViewer />
              </TabPanel>
            </TabPanels>
          </Tabs>
        </Split>
      </Split>
    </Layout>
  );
};

export default App;