module.exports = {
  root: true,
  env: {
    node: true
  },
  extends: ["plugin:vue/essential", "@vue/prettier"],
  rules: {
    "no-console": process.env.NODE_ENV === "production" ? "warn" : "off",
    "no-debugger": process.env.NODE_ENV === "production" ? "warn" : "off",
    'prettier/prettier': [
      "error",
      { trailingComma: 'es5', singleQuote: true, semi: true },
    ],
  },
  parserOptions: {
    parser: "babel-eslint"
  }
};
