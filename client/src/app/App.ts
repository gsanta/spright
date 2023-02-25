import EditorEvents from '@/services/editor/EditorEvents';
import ToolStore from '@/panels/toolbar/ToolStore';
import { createContext } from 'react';
import ModuleManager from './ModuleManager';
import KeyboardHandler from '@/services/keyboard/KeyboardHandler';
import Editor from '@/services/editor/Editor';
import LayerHandler from '@/panels/layer/model/LayerHandler';
import EditorStore from '@/services/settings/EditorStore';

export type App = {
  editorApi: Editor;
  toolStore: ToolStore;
  editorStore: EditorStore;
  editorEvents: EditorEvents;
  moduleManager: ModuleManager;
  keyboardHandler: KeyboardHandler;
  layerHandler: LayerHandler;
};

export const AppContext = createContext<App | undefined>(undefined);

export default App;
