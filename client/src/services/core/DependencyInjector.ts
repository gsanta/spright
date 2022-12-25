import { App } from '@/core/App';
import KeyCode from '../keyboard/KeyCode';
import ExternalTool from '../../panels/toolbar/model/ExternalTool';
import ToolName from '../../panels/toolbar/model/ToolName';
import ToolSelectionEvent from '../../panels/toolbar/model/ToolSelectionEvents';
import LifeCycleEventListener from './LifeCycleEventListener';
import PreviewModule from '@/panels/preview/PreviewModule';

class DependencyInjector implements LifeCycleEventListener {
  onCanvasInitialized({ canvasEventHandler, editorApi, toolStore, keyboardHandler, layerHandler, moduleManager }: App) {
    toolStore.addTool(
      new ExternalTool(
        ToolName.Brush,
        'BiPencil',
        editorApi,
        new ToolSelectionEvent(toolStore, ToolName.Brush, KeyCode.b),
      ),
    );
    toolStore.addTool(new ExternalTool(ToolName.Rectangle, 'BiRectangle', editorApi));
    toolStore.addTool(new ExternalTool(ToolName.SelectionRectangle, 'BiBorderRadius', editorApi));
    toolStore.addTool(new ExternalTool(ToolName.Erase, 'BiEraser', editorApi));
    toolStore.addTool(new ExternalTool(ToolName.Pan, 'BiMove', editorApi));
    toolStore.addTool(new ExternalTool(ToolName.PaintBucket, 'BiColorFill', editorApi));
    toolStore.addTool(new ExternalTool(ToolName.ColorPicker, 'BiHighlight', editorApi));
    toolStore.setSelectedTool(ToolName.Brush);

    moduleManager.addModule(new PreviewModule(canvasEventHandler, editorApi));

    moduleManager.start();

    layerHandler.init();

    toolStore.tools.forEach((tool) => {
      const shortCut = tool.getShortCut();
      if (shortCut) {
        keyboardHandler.addKeyEvent(shortCut);
      }
    });
  }
}

export default DependencyInjector;
