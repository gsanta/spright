import { ComponentStyleConfig, defineStyle, theme } from '@chakra-ui/react';
import { mode } from '@chakra-ui/theme-tools';

// const disabled = {
//   bgColor: 'gray.600',
//   cursor: 'not-allowed',
// };

const variantOutline = defineStyle((props) => {
  const { colorScheme: c } = props;
  const defaultTheme = theme.components.Button.variants?.outline(props);

  if (c === 'gray') {
    return { ...defaultTheme };
  }

  const borderColor = mode(`gray.200`, `${c}.400`)(props);

  return {
    ...defaultTheme,
    bg: mode(`${c}.200`, `${c}.500`)(props),
    color: 'white',
    border: '1px solid',
    borderColor,
    _hover: {
      bg: mode(`${c}.50`, `${c}.400`)(props),
    },
    _active: {
      bg: mode(`${c}.100`, `${c}.300`)(props),
    },
  };
});

const variantSolid = defineStyle((props) => {
  const { colorScheme: c } = props;
  const defaultTheme = theme.components.Button.variants?.solid(props);
  const bg = mode(`${c}.200`, `${c}.600`)(props);

  return {
    ...defaultTheme,
    bg,
    color: 'white',
    _hover: {
      bg: mode(`${c}.50`, `${c}.500`)(props),
      _disabled: {
        bg,
      },
    },
    _active: {
      bg: mode(`${c}.100`, `${c}.500`)(props),
    },
  };
});

const ButtonTheme: ComponentStyleConfig = {
  baseStyle: {
    '.chakra-button__icon': {
      marginInlineEnd: 0,
    },
    padding: '2px',
    '&.iconOnly': {
      px: '1px',
      py: '1px',
      paddingY: '1px',
      paddingX: '2px',
    },
    _active: {
      bg: 'gray.400',
    },
    _disabled: {
      opacity: 0.4,
      cursor: 'not-allowed',
      boxShadow: 'none',
    },
  },
  variants: {
    outline: variantOutline,
    solid: variantSolid,
  },
};

export default ButtonTheme;