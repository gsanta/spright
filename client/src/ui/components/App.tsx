import React, { useCallback, useEffect, useState } from 'react';
import { ChakraProvider } from '@chakra-ui/react';
import '../../app.scss';
import Layout from './layout/Layout';
import Box from './box/Box';
import ExternalTool from '@/services/tool/ExternalTool';
import ToolStore from '@/services/tool/ToolStore';
import Toolbar from '../panels/toolbar/Toolbar';
import theme from './theme';
import ToolName from '@/services/tool/ToolName';
import Split from 'react-split';
import { useResizeObserver } from '../hooks/useResizeObserver';

const App = () => {
  const [isModuleSet, setIsModuleSet] = useState(false);
  const [toolStore, setToolStore] = useState<ToolStore | undefined>();
  const [canvasNode, setCanvasNode] = useState<HTMLElement | undefined>(undefined);

  const setWindowSize = () => {
    if (canvasNode && isModuleSet) {
      const rect = canvasNode.getBoundingClientRect();
      window.Module.setWindowSize(rect.width, rect.height);
    }
  };

  // eslint-disable-next-line react-hooks/exhaustive-deps
  useEffect(() => {
    if (window?.Module?.isRuntimeInitialize && !isModuleSet) {
      setIsModuleSet(true);
      setWindowSize();

      const tools = [
        new ExternalTool(ToolName.Brush, 'BiPencil', Module),
        new ExternalTool(ToolName.Rectangle, 'BiRectangle', Module),
        new ExternalTool(ToolName.SelectionRectangle, 'BiBorderRadius', Module),
        new ExternalTool(ToolName.Erase, 'BiEraser', Module),
      ];
      setToolStore(new ToolStore(tools));
    }
  });

  const contentRef = useCallback((node: HTMLDivElement) => {
    if (node) {
      setCanvasNode(node);
    }
  }, []);

  useResizeObserver(canvasNode, setWindowSize);

  return (
    <ChakraProvider theme={theme} cssVarsRoot="body">
      <Layout
        header={
          <Box bgColor="blackAlpha.800" height="40px">
            Header
          </Box>
        }
        footer={
          <Box bgColor="blackAlpha.800" height="40px">
            Footer
          </Box>
        }
      >
        <Box display="flex" flexDirection="row">
          <Box width="50px">
            <Toolbar toolStore={toolStore} />
          </Box>
          <Split className="split" direction="horizontal" sizes={[75, 25]}>
            <Box ref={contentRef}>
              <canvas id="canvas"></canvas>
            </Box>
            <Box height="100%">
              <iframe src="iframe.html" height="500px" width="500px" />
            </Box>
          </Split>
        </Box>
      </Layout>
    </ChakraProvider>
  );
};

export default App;
