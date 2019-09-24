<template>
  <p>
    <b-field class="level" grouped>
      <p class="control">Brightness</p>
      <b-slider
        v-model="settings.brightness"
        :min="0"
        :max="16"
        ticks
      ></b-slider>
    </b-field>
    <b-field class="level" grouped>
      <p class="control">Scroll wait</p>
      <b-select :value="-1" v-model="settings.scrollWait" expanded>
        <option v-for="v in scrollWaits" :value="v.value" :key="v.value">{{
          v.label
        }}</option>
      </b-select>
    </b-field>
  </p>
</template>

<script>
import { mapActions, mapState } from 'vuex';
import pick from 'lodash/pick';
import range from 'lodash/range';
import debounce from 'lodash/debounce';

const scrollWaits = range(0, 11).map(v => ({
  value: v * 10,
  label: v ? `${v * 10} ms` : `Stopped`,
}));

export default {
  props: {
    isApplying: Boolean,
  },
  data() {
    return {
      scrollWaits,
      settings: {
        brightness: null,
        scrollWait: null,
      },
      inited: false,
    };
  },
  computed: {
    ...mapState(['deviceSettings']),
  },
  methods: {
    ...mapActions(['postDeviceSettings']),
    updateSettings: debounce(async function() {
      const settings = { ...this.deviceSettings, ...this.settings };
      await this.postDeviceSettings(settings);
      this.$emit('update:isApplying', false);
    }, 500),
  },
  watch: {
    settings: {
      deep: true,
      handler() {
        if (!this.inited) {
          this.inited = true;
          return;
        }
        this.$emit('update:isApplying', true);
        this.updateSettings();
      },
    },
  },
  mounted() {
    this.settings = pick(this.deviceSettings, ['brightness', 'scrollWait']);
  },
};
</script>
