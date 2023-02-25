import Box from '@/ui/components/box/Box';
import useAppContext from '@/ui/hooks/useAppContext';
import { useResizeObserver } from '@/ui/hooks/useResizeObserver';
import { forwardRef } from '@chakra-ui/react';
import React, { useCallback, useEffect, useRef, useState } from 'react';
import { useDebounce } from 'usehooks-ts';

const Canvas = forwardRef((_props, ref) => {
  const { editorApi } = useAppContext();
  const [width, setWidth] = useState(100);
  const [height, setHeight] = useState(100);
  const debouncedWidth = useDebounce(width, 200);
  const debouncedHeight = useDebounce(height, 200);

  const canvasParentRef = useRef<HTMLDivElement>(null);

  const resize = useCallback(() => {
    if (canvasParentRef.current) {
      setWidth(canvasParentRef.current.offsetWidth);
      setHeight(canvasParentRef.current.offsetHeight);
    }
  }, []);

  useEffect(() => {
    if (editorApi.isRuntimeInitialized) {
      editorApi.setWindowSize(debouncedWidth, debouncedHeight);
    }
  }, [editorApi, debouncedWidth, debouncedHeight]);

  useResizeObserver(canvasParentRef.current, resize);

  return (
    <Box display="flex" height="100%" justifyContent="space-around" overflow="hidden" ref={canvasParentRef}>
      <Box as="canvas" id="canvas" ref={ref} width={debouncedWidth} height={debouncedHeight}></Box>
    </Box>
  );
});

export default Canvas;
