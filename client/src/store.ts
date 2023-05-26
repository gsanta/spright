import { configureStore } from '@reduxjs/toolkit';
import frameSlice from './features/frame/state/frameSlice';
import settingsSlice from './features/settings/state/settingsSlice';
import toolSlice from './features/tool/state/toolSlice';
import layerSlice from './panels/layer/state/layerSlice';
import userSlice from './features/user/userSlice';

export const store = configureStore({
  reducer: {
    frame: frameSlice,
    layer: layerSlice,
    settings: settingsSlice,
    tool: toolSlice,
    user: userSlice,
  },
  middleware: (getDefaultMiddleware) =>
    getDefaultMiddleware({
      serializableCheck: {
        ignoredActions: ['frame/initFrames', 'layer/initLayers', 'tool/initTools', 'settings/initSettings'],
        ignoredPaths: ['frame.editor', 'layer.editor', 'settings.editor', 'tool.editor'],
      },
    }),
});

export type RootState = ReturnType<typeof store.getState>;
export type AppDispatch = typeof store.dispatch;
